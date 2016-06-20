//
// Created by Yorick Rommers on 2016/06/08.
//

#include "Util.h"
#include <thread>
#include "HeadTracking.h"

using namespace cv;

/* Function Headers */
std::vector<Rect> detectFace(Mat frame);

CascadeClassifier face_cascade;
unsigned int times_updated = 0;


HeadTracking::~HeadTracking() {

}

HeadTracking::HeadTracking(std::vector<Player *> players) {
    this->players = players;
}

bool isSamePoint(Point p1, Point p2) {
    if (abs(p1.x - p2.x) < 10 &&
        abs(p1.y - p2.y) < 10) {
        //This is the same rectangle
//
        return true;
    }
    return false;
}

// Detect face
std::vector<std::pair<int, Point>> detectFace(Mat frame, unsigned int playerSize) {

    std::vector<pair<int, Point>> retFaces;
    std::vector<Rect> faces;
    Mat frame_gray;
    int minNeighbors = 2;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);   // Convert to gray
    equalizeHist(frame_gray, frame_gray);          // Equalize histogram

    // Detect face with open source cascade
    face_cascade.detectMultiScale(frame_gray, faces,
                                  1.1, minNeighbors,
                                  0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    for (size_t i = 0; i < faces.size(); i++) {
        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        if(playerSize == 1){
            retFaces.push_back(pair<int, Point>(0, center));
        }
        else{
            if (center.x > (frame.size().width) / 2) { //If left player
                //printf("center x is %d\n frame size width /2 is %d\n", center.x, (frame.size().width) / 2);
                //printf("left player \n");
                retFaces.push_back(pair<int, Point>(0, center));
            }
            else {
                //printf("center x is %d\n frame size width /2 is %d\n", center.x, (frame.size().width) / 2);
                //printf("right player \n");
                retFaces.push_back(pair<int, Point>(1, center));
            }
        }

    }
    return retFaces;
}

//Returning between -2f and 2f using this function
float calcHeadPos(int pos, int camwidth) {
    return (pos / (float) camwidth)*6.0f - 3.0f;
}

void HeadTracking::cameraThreadFunc() {
    VideoCapture cap(0); // capture from default camera
    Mat frame;
    int camWidth = 640, camHeight = 480;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, camWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, camHeight);

	std::string file = "opencv_xml/haarcascade_frontalface_alt.xml";
#if __APPLE__
	file = "Project/" + file;
#endif
    face_cascade.load(file); // load face classifiers
//    eyes_cascade.load("Project/opencv_xml/haarcascade_eye_tree_eyeglasses.xml"); // load eye classifiers

    std::vector<pair<int, Point>> points;
    while (cap.read(frame)) {
        if (!frame.empty()) {
            points = detectFace(frame, (unsigned int) players.size());
            //printf("points contains \n");
            for (auto &face : points) {
                //printf("Face %d pos %d %d\n", face.first, face.second.x, face.second.y);
            }
            for (auto &face : points) {
                //printf("-------------------------\nFace %d %d\n", face.second.x, face.second.y);
//                printf("Setting headtrack to %d : %f\n", face.first, calcHeadPos(face.second.x, camWidth));
                if (face.first == 0) { //if player 0
                    //printf("PlayerID is %d \n", players[0]->getPlayerID());
                    players[0]->getCamera()->headtrack_x = calcHeadPos(face.second.x, camWidth);
                }
                else if(face.first == 1){
                    players.at(1)->getCamera()->headtrack_x = calcHeadPos(face.second.x, camWidth);
                }
            }
			Util::USleep(100);
			//usleep(1000 * (1000 / 100));
        }
    }
}

void HeadTracking::initThread() {
    std::thread cameraThread(&HeadTracking::cameraThreadFunc, this); //Camerathread
    cameraThread.detach();
}







