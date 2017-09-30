#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <dlib/image_processing/frontal_face_detector.h>
//#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>

#include <dlib/image_io.h>
//#include <dlib/gui_widgets.h>

#include <opencv2/core/core.hpp>

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    try
    {
        // We need a face detector.  We will use this to get bounding boxes for
        // each face in an image.
        frontal_face_detector detector = get_frontal_face_detector();

        // And we also need a shape_predictor.  This is the tool that will predict face
        // landmark positions given an image and face bounding box.  Here we are just
        // loading the model from the shape_predictor_68_face_landmarks.dat file you gave
        // as a command line argument.
        shape_predictor sp;

        deserialize("./shape_predictor_68_face_landmarks.dat") >> sp;

        //image_window win, win_faces;
        // Loop over all the images provided on the command line.
        for (int i = 1; i < argc; ++i)
        {
            cout << "processing image " << argv[i]<< endl;
            array2d<rgb_pixel> img;
            load_image(img, argv[i]);
            // Make the image larger so we can detect small faces.
            pyramid_up(img);

            // Now tell the face detector to give us a list of bounding boxes
            // around all the faces in the image.
            long long detec_time = cv::getTickCount();
            std::vector<rectangle> dets = detector(img);
            detec_time = cv::getTickCount() - detec_time;
            cout << "detect time : " << 1000 * detec_time / cv::getTickFrequency() << " ms" << endl;
            cout << "Number of faces detected: " << dets.size() << endl;

            // Now we will go ask the shape_predictor to tell us the pose of
            // each face we detected.
            std::vector<full_object_detection> shapes;

            //int64 t;
            long long total = cv::getTickCount();
            for (unsigned long j = 0; j < dets.size(); ++j)
            {
                long long t = cv::getTickCount();
                full_object_detection shape = sp(img, dets[j]);
                t = cv::getTickCount() - t;
                cout << "process time : " << 1000 * t / cv::getTickFrequency() << " ms" << endl;

                cout << "number of parts: " << shape.num_parts() << endl;
                cout << "pixel position of first part:  " << shape.part(0) << endl;
                cout << "pixel position of second part: " << shape.part(1) << endl;
                // You get the idea, you can get all the face part locations if
                // you want them.  Here we just store them in shapes so we can
                // put them on the screen.
                shapes.push_back(shape);

                total = cv::getTickCount() - total;
                cout << "total landmark process time : " << 1000 * total / cv::getTickFrequency() << " ms" << endl;

                // Now let's view our face poses on the screen.
                //win.clear_overlay();
                //win.set_image(img);
                //win.add_overlay(render_face_detections(shapes));

                // We can also extract copies of each face that are cropped, rotated upright,
                // and scaled to a standard size as shown here:
                //dlib::array<array2d<rgb_pixel> > face_chips;
                //extract_image_chips(img, get_face_chip_details(shapes), face_chips);
                //win_faces.set_image(tile_images(face_chips));

                //if (dets.size()>0)
                //{
                //char str[10];
                //sprintf(str, "saved_img_%d.jpg", i);
                //const string source = string(str);
                //save_jpeg(tile_images(face_chips), source, 75);
                //picNo = picNo + 1;
                ////cout << picNo << endl;
                //}


            }

            cout << "Hit enter to process the next image..." << endl;
            cin.get();
        }
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
    return 0;
}

// ----------------------------------------------------------------------------------------
