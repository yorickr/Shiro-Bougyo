//
// Created by Yorick Rommers on 2016/06/08.
//

#include <zconf.h>
#include <thread>
#include "HeadTracking.h"

using namespace cv;
/* Function Headers */
std::vector<Rect> detectFace( Mat frame);

CascadeClassifier face_cascade;

HeadTracking::~HeadTracking() {

}

HeadTracking::HeadTracking(std::vector<Player *> players) {
    this->players = players;
}

// Detect face and display it
std::vector<Rect> detectFace(Mat frame) {

    std::vector<Rect> retFaces;
    std::vector<Rect> faces;
    Mat frame_gray, frame_lab, output, temp;
//    int h = frame.size().height - 1;
//    int w = frame.size().width - 1;
    int minNeighbors = 2;
//    bool faceNotFound = false;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);   // Convert to gray
    equalizeHist(frame_gray, frame_gray);          // Equalize histogram

    // Detect face with open source cascade
    face_cascade.detectMultiScale(frame_gray, faces,
                                  1.1, minNeighbors,
                                  0|CASCADE_SCALE_IMAGE, Size(30, 30));

    for(size_t i = 0; i < faces.size(); i++){
//        Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);

//        Mat face = frame_gray(faces[i]);
//        std::vector<Rect> eyes;

        // Try to detect eyes, inside each face
//        eyes_cascade.detectMultiScale(face, eyes, 1.1, 2,
//                                      0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

//        if(eyes.size() > 0) //face found
        //filter here
        retFaces.push_back(faces[i]);
    }

    return retFaces;
}

void HeadTracking::cameraThreadFunc() {
    VideoCapture cap(0); // capture from default camera
    Mat frame;
    int camWidth = 640, camHeight =480;
    cap.set(CV_CAP_PROP_FRAME_WIDTH,camWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,camHeight);

    face_cascade.load("Project/opencv_xml/haarcascade_frontalface_alt.xml"); // load face classifiers
//    eyes_cascade.load("Project/opencv_xml/haarcascade_eye_tree_eyeglasses.xml"); // load eye classifiers
    while(cap.read(frame)) {
        if(!frame.empty()){
            for(auto &face : detectFace(frame)) {
                printf("-------------------------\nFace %d %d\n", face.x, face.y);
                players.at(0)->getCamera()->headtrack_x = (face.x / (float)camWidth) * 2.0f -1.0f; //headtrakc x goes from -1 to 1
//                headtrack_y = (face.y / (float)camHeight) * 2.0f -1.0f;
            }
            usleep(1000/60);
        }
    }
}

void HeadTracking::initThread() {
    std::thread cameraThread(&HeadTracking::cameraThreadFunc, this); //Camerathread
    cameraThread.detach();
}







