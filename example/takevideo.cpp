#include <lccv.hpp>
#include <opencv2/opencv.hpp>

int main()
{
    std::cout<<"Sample program for LCCV video capture"<<std::endl;
    std::cout<<"Press ESC to stop."<<std::endl;
    cv::Mat image;
    lccv::PiCamera cam;
    cam.options->video_width=1920;
    cam.options->video_height=1080;
    cam.options->framerate=60;
    cam.options->verbose=true;

    auto lens_position = 1.f;
    cv::namedWindow("Video",cv::WINDOW_NORMAL);
    cv::resizeWindow("Video", cam.options->video_width, cam.options->video_height);
    cam.startVideo();
    int ch=0;
    while(ch!=27){
        if(!cam.getVideoFrame(image,1000)){
            std::cout<<"Timeout error"<<std::endl;
        }
        else{
            cv::imshow("Video",image);
            ch=cv::waitKey(10);
            if(ch == 'z'){
                std::cout << "Activate auto focus mode continuous focus top left" << std::endl;
                cam.options->auto_focus_mode=libcamera::controls::AfModeContinuous;
                cam.options->auto_focus_x = 0.0;
                cam.options->auto_focus_y = 0.0;
                cam.options->auto_focus_width = 0.2;
                cam.options->auto_focus_height = 0.2;
                cam.ApplyFocusOptions();
            }
            if(ch == 'x'){
                std::cout << "Activate auto focus mode continuous bottom right" << std::endl;
                cam.options->auto_focus_mode=libcamera::controls::AfModeContinuous;
                cam.options->auto_focus_x = 0.8;
                cam.options->auto_focus_y = 0.8;
                cam.options->auto_focus_width = 0.2;
                cam.options->auto_focus_height = 0.2;
                cam.ApplyFocusOptions();
            }
            if(ch == 'm'){
                std::cout << "Activate auto focus mode manual and les position 6" << std::endl;
                cam.options->auto_focus_mode=libcamera::controls::AfModeManual;
                cam.options->lens_position=lens_position;
                cam.ApplyFocusOptions();
            }
            if(ch == ',' || ch == '.'){
                cam.options->auto_focus_mode=libcamera::controls::AfModeManual;
                lens_position = (ch == ',') ? lens_position - 1.f : lens_position + 1.f;
                lens_position = std::clamp(lens_position, 0.f, 50.f);
                cam.options->lens_position=lens_position;
                cam.ApplyFocusOptions();
            }
            if(ch == 'c'){
                std::cout << "Activate auto focus mode continuous" << std::endl;
                cam.options->auto_focus_mode=libcamera::controls::AfModeContinuous;
                cam.ApplyFocusOptions();
            }
        }
    }
    cam.stopVideo();
    cv::destroyWindow("Video");
}
