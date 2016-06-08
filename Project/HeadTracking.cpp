//
// Created by Yorick Rommers on 2016/06/08.
//

#include <zconf.h>
#include <thread>
#include "HeadTracking.h"

using namespace cv;

/* Function Headers */
std::vector<Rect> detectFace(Mat frame);

CascadeClassifier face_cascade;

HeadTracking::~HeadTracking() {

}

HeadTracking::HeadTracking(std::vector<Player *> players) {
    this->players = players;
}

bool isSamePoint(Point p1, Point p2) {
    if (abs(p1.x - p2.x) < 10 &&
        abs(p1.y - p2.y) < 10) {
        //This is the same rectangle
//        printf("same rect-----------\n");
        if (abs(p1.x - p2.x) > 7 &&
            abs(p1.y - p2.y) > 7) {
            //Check if rectangle has moved enough
//            printf("moved enough-----------\n");
        }
    }
}

// Detect face and display it
std::vector<Point> detectFace(Mat frame, std::vector<Point> prevPoint) {

    std::vector<Point> retFaces;
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
                                  0 | CASCADE_SCALE_IMAGE, Size(30, 30));
//    face_cascade.detectMultiScale(frame_gray, faces, 1.2, 4, CV_HAAR_DO_CANNY_PRUNING, cvSize(30, 30));// if captured through WebCam
    printf("start of loop-----------\n");
    printf("prevpoint contains-----------\n");
    for (auto &item : prevPoint) {
        printf("Prevpt %d %d\n", item.x, item.y);
    }
    bool foundFaces = false;
    if (prevPoint.size() >= 1) { //if we've previously found faces
        foundFaces = true;
    }

    for (size_t i = 0; i < faces.size(); i++) {
        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        if(foundFaces){
            retFaces.push_back(center);
        }
        else{
            for (auto &prevp : prevPoint) {
                printf("Prev %d %d\n", prevp.x, prevp.y);
                printf("found %d %d\n", center.x, center.y);

            }
        }
        printf("end of faces-----------\n");
    }
    printf("retfaces contains -----------\n");
    for (auto &m : retFaces) {
        printf("%d %d\n", m.x, m.y);
    }
    printf("end of retfaces-----------\n");

    return retFaces;
}

void HeadTracking::cameraThreadFunc() {
    VideoCapture cap(0); // capture from default camera
    Mat frame;
    int camWidth = 640, camHeight = 480;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, camWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, camHeight);

    face_cascade.load("Project/opencv_xml/haarcascade_frontalface_alt.xml"); // load face classifiers
//    eyes_cascade.load("Project/opencv_xml/haarcascade_eye_tree_eyeglasses.xml"); // load eye classifiers

    std::vector<Point> points;
    while (cap.read(frame)) {
        if (!frame.empty()) {
            points = detectFace(frame, points);
            for (auto &face : points) {
                printf("-------------------------\nFace %d %d\n", face.x, face.y);
                printf("Setting headtrack to %f\n", (face.x / (float) camWidth) * 3.0f - 1.0f);
                players.at(0)->getCamera()->headtrack_x =
                        (face.x / (float) camWidth) * 3.0f - 1.0f; //headtrakc x goes from -1 to 1
//                headtrack_y = (face.y / (float)camHeight) * 2.0f -1.0f;
            }
            usleep(1000 * 60);
        }
    }
}

void HeadTracking::initThread() {
    std::thread cameraThread(&HeadTracking::cameraThreadFunc, this); //Camerathread
    cameraThread.detach();
}







