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
//    cam.options->auto_focus_mode=libcamera::controls::AfModeContinuous;

//    cam.options->auto_focus_mode=libcamera::controls::AfModeManual;
//    cam.options->lens_position=6.f;

    cam.options->auto_focus_mode=libcamera::controls::AfModeContinuous;
    cam.options->auto_focus_x = 0.8;
    cam.options->auto_focus_y = 0.8;
    cam.options->auto_focus_width = 0.2;
    cam.options->auto_focus_height = 0.2;

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
        }
    }
    cam.stopVideo();
    cv::destroyWindow("Video");
}
