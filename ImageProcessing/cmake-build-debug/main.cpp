//
// Created by jordan gillispie on 3/20/22.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

// create a struct for the header file information
struct Header{
    char  idLength;
    char  colorMapType;
    char  dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char  bitsPerPixel;
    char  imageDescriptor;
};

// create a struct for the pixels
// R G B each have values from 0-255
struct pixel{
    unsigned char b;
    unsigned char g;
    unsigned char r;
};

void parseInFile(const string &filePath, Header &headerIn, vector<pixel> &pixelVectorIn) {

    ifstream readfile(filePath,ios_base::in | ios::binary);

    readfile.read(&headerIn.idLength, sizeof(headerIn.idLength));

    readfile.read(&headerIn.colorMapType, sizeof (headerIn.colorMapType));

    readfile.read(&headerIn.dataTypeCode, sizeof(headerIn.dataTypeCode));

    readfile.read((char*)&headerIn.colorMapOrigin, sizeof(headerIn.colorMapOrigin));

    readfile.read((char*)&headerIn.colorMapLength, sizeof(headerIn.colorMapLength));

    readfile.read((char*)&headerIn.colorMapDepth, sizeof(headerIn.colorMapDepth));

    readfile.read((char*)&headerIn.xOrigin, sizeof(headerIn.xOrigin));

    readfile.read((char*)&headerIn.yOrigin, sizeof(headerIn.yOrigin));

    readfile.read((char*)&headerIn.width, sizeof(headerIn.width));

    readfile.read((char*)&headerIn.height, sizeof(headerIn.height));

    readfile.read((char*)&headerIn.bitsPerPixel, sizeof(headerIn.bitsPerPixel));

    readfile.read((char*)&headerIn.imageDescriptor, sizeof(headerIn.imageDescriptor));

    /*** NOW AT THE IMAGE DATA ***/
    // size of the loop is equal to image dimensions
    int imageSize = headerIn.width * headerIn.height;

    // loop the image based on size
    // each index has one pixel with 3 bytes
    // each byte can be read and then stored in the pixel object
    // each time it is stored, push back the object into the vector of pixels
    // at the end we should have all the pixels stored in a vector representing the image
    for(int i = 0; i < imageSize; i++){

        // at position 0 in the vector we can store 3 pieces of color data into the pixel object by reading it
        pixel currentPixel;

        // read b
        readfile.read((char*) &currentPixel.b, sizeof(currentPixel.b));

        // read g
        readfile.read((char*) &currentPixel.g, sizeof(currentPixel.g));

        // read r
        readfile.read((char*) &currentPixel.r, sizeof(currentPixel.r));

        // store the object in the vector
        pixelVectorIn.push_back(currentPixel);
    }
}

// now i need to write out all the data to a new output file
// take in the name of an outfile, take in the header object to print its data, take in the pixel vector to put out its data too
void createNewFile(const string &outFilePath, Header &headerOut, vector<pixel> &pixelOut){

    // figure out where to send it
    ofstream outFile(outFilePath, ios_base :: out);

    // "write" all the header info from the object we pass in
    outFile.write((char*)&headerOut.idLength, sizeof(headerOut.idLength));

    outFile.write((char*)&headerOut.colorMapType, sizeof (headerOut.colorMapType));

    outFile.write((char*)&headerOut.dataTypeCode, sizeof(headerOut.dataTypeCode));

    outFile.write((char*)&headerOut.colorMapOrigin, sizeof(headerOut.colorMapOrigin));

    outFile.write((char*)&headerOut.colorMapLength, sizeof(headerOut.colorMapLength));

    outFile.write((char*)&headerOut.colorMapDepth, sizeof(headerOut.colorMapDepth));

    outFile.write((char*)&headerOut.xOrigin, sizeof(headerOut.xOrigin));

    outFile.write((char*)&headerOut.yOrigin, sizeof(headerOut.yOrigin));

    outFile.write((char*)&headerOut.width, sizeof(headerOut.width));

    outFile.write((char*)&headerOut.height, sizeof(headerOut.height));

    outFile.write((char*)&headerOut.bitsPerPixel, sizeof(headerOut.bitsPerPixel));

    outFile.write((char*)&headerOut.imageDescriptor, sizeof(headerOut.imageDescriptor));

    // "write" each pixels data back out
    // loop through and write  b g r
    for(int i = 0; i < pixelOut.size(); i++){

        // currentpixel should go through each pixel in the vector
        pixel currentPixel = pixelOut[i];

        // write b
        outFile.write((char*) &currentPixel.b, sizeof(currentPixel.b));

        // write g
        outFile.write((char*) &currentPixel.g, sizeof(currentPixel.g));

        // write r
        outFile.write((char*) &currentPixel.r, sizeof(currentPixel.r));
    }
}

// function to compare output file to example file
// should take in the right example file and the output file we created
// we can parse and gather the information inside the function

// for loop to go through the vectors

// if examplefile.rgb != outputfile.rgb --> use or statement to see if any of the three r not equal

// print "there is a mistake at pixel i"
    // expected r value:
    // output r value:
    // do for all
void imageTest(const string exampleFile, const string myOutputFile){

    // parse both files
    Header exampleHeader;
    vector<pixel> exampleVector;
    parseInFile(exampleFile, exampleHeader, exampleVector);

    Header myHeader;
    vector<pixel> myVector;
    parseInFile(myOutputFile,myHeader,myVector);

    for (int i = 0; i < myVector.size(); i++){

        if((int)exampleVector[i].r != (int)myVector[i].r){
            cout << "Mistake at pixel: " << i << endl;
            cout << "Expected r value: " << (int)exampleVector[i].r << endl;
            cout << "My r value: " << (int)myVector[i].r << endl;
            cout << endl;
        }
        if((int)exampleVector[i].g != (int)myVector[i].g){
            cout << "Mistake at pixel: " << i << endl;
            cout << "Expected g value: " << (int)exampleVector[i].g << endl;
            cout << "My g value: " << (int)myVector[i].g << endl;
            cout << endl;
        }
        if((int)exampleVector[i].b != (int)myVector[i].b){
            cout << "Mistake at pixel: " << i << endl;
            cout << "Expected b value: " << (int)exampleVector[i].b << endl;
            cout << "My b value: " << (int)myVector[i].b << endl;
            cout << endl;
        }
    }
}

// function to multiply files together for task 1
// needs to take in vectorpixel data for both layers
// vectors already have the dimensions calculated, each element in the vector is a pixel containing R G B

// cast the values to int, multiply the values, then divide them by 255 so that they can be stored in the unsigned int char type

// loop through the vector of layer one

    // int red = ((int)layerone[i].r * (int)layertwo[i].r ) / 255
    // int green = (layerone.g * layertwo.g ) / 255
    // int blue = (layerone.b * layertwo.b ) / 255

    // newpixel.r = (unsigned char)red
    // newpixel.g = (unsigned char)green
    // newpixel.b = (unsigned char)blue

    // whenever a new pixel is created, store it in a newvector so that we can write it out later
    // now new vector will have the transformed image at the end of the loop

// write a new file that uses the layerone header object, and the new vector that we created
// we can have it return the new vector and then in main we can use the createNewFile() to specify the outpath
vector<pixel> taskOne(vector<pixel> &layerOne, vector<pixel> &layerTwo){

    // vector to return
    vector<pixel> partOneVector;
    for(int i = 0; i < layerOne.size(); i++){

        float red = ((float)layerOne[i].r * (float)layerTwo[i].r) / 255;
        red += 0.5f;
        float green = ((float)layerOne[i].g * (float)layerTwo[i].g) / 255;
        green += 0.5f;
        float blue = ((float)layerOne[i].b * (float)layerTwo[i].b) / 255;
        blue += 0.5f;

        pixel pixelNew;
        pixelNew.r = (unsigned char)red;
        pixelNew.g = (unsigned char)green;
        pixelNew.b = (unsigned char)blue;

        partOneVector.push_back(pixelNew);
    }
    return partOneVector;
}

// function to clamp
int clamp(int value, int min, int max){
    if (value < min){
        value = min;
        return value;
    }
    else if(value > max){
        value = max;
        return value;
    }
    else{
        return value;
    }
}

// function for task two
/* If v compares less than lo, returns lo; otherwise if hi compares less than v, returns hi; otherwise returns v.
 Uses operator< to compare the values. */
// syntax: clamp(calculated value, min, max)
    // will return the value if its between min and max
    // return min if its less than min
    // return max if its greater than max

// function takes in 2 vectors that will be operated on

// loop through the vector
// int red = layer2.r
//
// int variable to gather the result of the calculation
// clamp the int from 0-255

vector<pixel> taskTwo(vector<pixel> &layerTwoVector, vector<pixel> &carvector){

    // vector to store new values and return at the end
    vector<pixel> partTwoVector;

    // go through the vector
    for(int i = 0; i < layerTwoVector.size(); i++){

        // create int variables to store the values of the subtraction calculations
        int red = ((int)carvector[i].r -  (int)layerTwoVector[i].r);
        int green = ((int)carvector[i].g - (int)layerTwoVector[i].g);
        int blue = ((int)carvector[i].b - (int)layerTwoVector[i].b);

        // clamp the values
        red = clamp(red, 0, 255);
        green = clamp(green, 0, 255);
        blue = clamp(blue, 0, 255);

        pixel pixelNew;
        pixelNew.r = (unsigned char)red;
        pixelNew.g = (unsigned char)green;
        pixelNew.b = (unsigned char)blue;

        partTwoVector.push_back(pixelNew);
    }
    return partTwoVector;
}

// function to screen for task 3
// new vector[i].rgb = 1 - ( (1 - multipliedVector) * (1 - rawNewVector) )

// function will take in the already converted vector and the textVector
// same as multiply but different calculations
//

vector<pixel> taskThree(vector<pixel> &convertedVector, vector<pixel> &textVector){

    // vector to return
    vector<pixel> partThreeVector;

    for(int i = 0; i < convertedVector.size(); i++){
        // new vector[i].rgb = 1 - ( (1 - multipliedVector) * (1 - rawNewVector) )

        // standardize values from both vectors
        float element1 = 1 -  ((float)convertedVector[i].r / 255);
        float element2 = 1 -  ((float)textVector[i].r / 255);
        // finish the calculation
        float red = 1 - ( element1 * element2);
        // convert back to nice char value
        red *= 255;
        red += 0.5f;

        // standardize values from both vectors
        element1 = 1 -  ((float)convertedVector[i].g / 255);
        element2 = 1 -  ((float)textVector[i].g / 255);
        // finish the calculation
        float green = 1 - ( element1 * element2);
        // convert back to nice char value
        green *= 255;
        green += 0.5f;

        // standardize values from both vectors
        element1 = 1 -  ((float)convertedVector[i].b/ 255);
        element2 = 1 -  ((float)textVector[i].b / 255);
        // finish the calculation
        float blue = 1 - ( element1 * element2);
        // convert back to nice char value
        blue *= 255;
        blue += 0.5f;

        pixel pixelNew;
        pixelNew.r = (unsigned char)red;
        pixelNew.g = (unsigned char)green;
        pixelNew.b = (unsigned char)blue;

        partThreeVector.push_back(pixelNew);
    }
    return partThreeVector;
}

// part 5 function
vector<pixel> taskFive(vector<pixel> &topLayer, vector<pixel> &bottomLayer){

    // vector to return at the end
    vector<pixel> returnVector;

    // scale all of the values first
    for (int i = 0; i < topLayer.size(); i++){

        float red1 = (float)topLayer[i].r / 255;
        float green1 = (float)topLayer[i].g / 255;
        float blue1 = (float)topLayer[i].b / 255;

        float red2 = (float)bottomLayer[i].r / 255;
        float green2 = (float)bottomLayer[i].g / 255;
        float blue2 = (float)bottomLayer[i].b / 255;

        // now that theyre all normalized create a new pixel based on greyscale
        pixel newPixel;

        if (red2 <= 0.5){
            float result = 2 * (red1 * red2);
            result *= 255;
            result += 0.5f;
            newPixel.r = (unsigned char)result;
        }
        if (green2 <= 0.5){
            float result = 2 * (green1 * green2);
            result *= 255;
            result += 0.5f;
            newPixel.g = (unsigned char)result;
        }
        if (blue2 <= 0.5){
            float result = 2 * (blue1 * blue2);
            result *= 255;
            result += 0.5f;
            newPixel.b = (unsigned char)result;
        }
        if (red2 > 0.5){
            float element1 = (1 - red1) * (1 - red2);
            float element2 = 1 - (2 * element1);
            element2 *= 255;
            element2 += 0.5f;
            newPixel.r = (unsigned char)element2;
        }
        if (green2 > 0.5){
            float element1 = (1 - green1) * (1 - green2);
            float element2 = 1 - (2 * element1);
            element2 *= 255;
            element2 += 0.5f;
            newPixel.g = (unsigned char)element2;
        }
        if (blue2 > 0.5){
            float element1 = (1 - blue1) * (1 - blue2);
            float element2 = 1 - (2 * element1);
            element2 *= 255;
            element2 += 0.5f;
            newPixel.b = (unsigned char)element2;
        }
        returnVector.push_back(newPixel);
    }
    return returnVector;
}

// task 6: add 200 to the green channel
vector<pixel> taskSix(vector<pixel> &greenery){
    vector<pixel> greenReturn;

    for (int i = 0; i < greenery.size(); i++){

        // add 200 to each of the green elements
        int green = (int)greenery[i].g + 200;

        green = clamp(green, 0, 255);

        pixel pixelNew;
        pixelNew.r = greenery[i].r;
        pixelNew.g = (unsigned char)green;
        pixelNew.b = greenery[i].b;

        greenReturn.push_back(pixelNew);
    }
    return greenReturn;
}

/*** TASK 7
     * Load “car.tga” and scale (multiply) the red channel by 4, and the blue channel by 0. This will
     increase the intensity of any red in the image, while negating any blue it may have.
     */
vector<pixel> taskSeven(vector<pixel> &carVector){

    vector<pixel> paintJob;

    for(int i = 0; i < carVector.size(); i++){

        float red = ((float)carVector[i].r * 4);
        red += 0.5f;
        red = (float)clamp((int)red, 0 , 255);

        float blue = ((float)carVector[i].b * 0);
        // blue += 0.5f;

        pixel pixelNew;
        pixelNew.r = (unsigned char)red;
        pixelNew.g = carVector[i].g;
        pixelNew.b = (unsigned char)blue;

        paintJob.push_back(pixelNew);

    }
    return paintJob;
}

/*** TASK 8
     * Load “car.tga” and write each channel to a separate file:
     * the red channel should be “part8_r.tga”,
     * the green channel should be “part8_g.tga”,
     * and the blue channel should be “part8_b.tga”
 (Hint: If your red channel image appears all red, try writing [Red, Red, Red] instead of [Red, 0, 0] to the file—ditto for green and blue!)
  ***/

// function for part8
// takes in the vector of car pixel data returns a vector of pixels where only the red channel exists
// take in a string to do each part in this task "red" for the red channel, etc.
// reassign b g to be red in a new vector of pixel

// if channel is == red, then
    // go through the size of the vector and at each index the value of red stays the same and the bg values are changed to red

vector<pixel> taskEight(const string &channel, vector<pixel> &carVector){

    // vector to that can be returned
    vector<pixel> modifiedImage;

    if (channel == "red"){

        for (int i = 0; i < carVector.size(); i++){

            // new pixel object
            pixel modifiedPixel;

            // create a new pixel with only the r values of the pixels we pass in
            modifiedPixel.r = carVector[i].r;
            modifiedPixel.g = carVector[i].r;
            modifiedPixel.b = carVector[i].r;

            modifiedImage.push_back(modifiedPixel);
        }
    }
    if (channel == "blue") {

        for (int i = 0; i < carVector.size(); i++) {

            // new pixel object
            pixel modifiedPixel;

            // create a new pixel with only the r values of the pixels we pass in
            modifiedPixel.r = carVector[i].b;
            modifiedPixel.g = carVector[i].b;
            modifiedPixel.b = carVector[i].b;

            modifiedImage.push_back(modifiedPixel);
        }
    }
    if (channel == "green") {

        for (int i = 0; i < carVector.size(); i++) {

            // new pixel object
            pixel modifiedPixel;

            // create a new pixel with only the r values of the pixels we pass in
            modifiedPixel.r = carVector[i].g;
            modifiedPixel.g = carVector[i].g;
            modifiedPixel.b = carVector[i].g;

            modifiedImage.push_back(modifiedPixel);
        }
    }
    return modifiedImage;
}

/*** TASK 9
 * Load “layer_red.tga”, “layer_green.tga” and “layer_blue.tga”, and combine the three files into one file.
 * The data from “layer_red.tga” is the red channel of the new image, layer_green is green, and layer_blue is blue.
***/
// this function can take in 3 vectors of pixels
// newPixel.r = all of the redlayer data
// newPixel.b = all of the blueLayer data
// new pixel.g = all of the greenLayer data

// now the new vector has info from each of the three layers at each pixel
// store them all into one vector and then return it
// return it and create a new file
vector<pixel> taskNine(vector<pixel> &red, vector<pixel> &blue, vector<pixel> &green){

    // vector to store pixels
    vector<pixel> combinedImage;
    for (int i = 0; i < red.size(); i++){

        // store data from each vector into a single pixel
        pixel pixelNew;
        pixelNew.r = red[i].r;
        pixelNew.b = blue[i].b;
        pixelNew.g = green[i].g;

        combinedImage.push_back(pixelNew);
    }
    return  combinedImage;
}

int main() {

    /*** TASK 1 ***/
    // load the layer1.tga file
    Header layerOneHeader;
    vector<pixel> layerOneVector;
    parseInFile("./input/layer1.tga", layerOneHeader, layerOneVector);

    // load the pattern1.tga file
    Header patternOneHeader;
    vector<pixel> patternOneVector;
    parseInFile("./input/pattern1.tga", patternOneHeader, patternOneVector);

    vector<pixel> partOneVector = taskOne(patternOneVector, layerOneVector);
    createNewFile("./output/part1.tga", layerOneHeader, partOneVector);

    // test pixel data
    imageTest("./examples/EXAMPLE_part1.tga", "./output/part1.tga");

    /*** TASK 2
     * Use the Subtract blending mode to combine “layer2.tga” (top layer) with “car.tga” (bottom layer).
     * This mode subtracts the top layer from the bottom layer.***/

    // load the layer2.tga file
    Header layerTwoHeader;
    vector<pixel> layerTwoVector;
    parseInFile("./input/layer2.tga", layerTwoHeader, layerTwoVector);

    // load the car.tga file
    Header carHeader;
    vector<pixel> carvector;
    parseInFile("./input/car.tga", carHeader, carvector);

    vector<pixel> partTwoVector = taskTwo(layerTwoVector, carvector);
    createNewFile("./output/part2.tga", layerTwoHeader, partTwoVector);

    // test pixel data
    imageTest("./examples/EXAMPLE_part2.tga", "./output/part2.tga");

    /*** TASK 3
     Use the Multiply blending mode to combine “layer1.tga” with “pattern2.tga”, and store the results temporarily.
     Load the image “text.tga” and, using that as the top layer,
     combine it with the previous results of layer1/pattern2 using the Screen blending mode.
     ***/

    Header layerOneHeader2;
    vector<pixel> layerOneVector2;
    parseInFile("./input/layer1.tga", layerOneHeader2, layerOneVector2);

    // load the pattern2.tga file
    Header patternTwoHeader;
    vector<pixel> patternTwoVector;
    parseInFile("./input/pattern2.tga", patternTwoHeader, patternTwoVector);

    // task one can multiply these bad boys together oh yeah
    vector<pixel> partThreeVector = taskOne(patternTwoVector, layerOneVector2);

    Header textFileHeader;
    vector<pixel> textFileVector;
    parseInFile("./input/text.tga", textFileHeader, textFileVector);

    // screen the textfilevector with partthreevector
    vector<pixel> screenVector =  taskThree(partThreeVector,textFileVector );

    createNewFile("./output/part3.tga", textFileHeader,screenVector);

    imageTest("./examples/EXAMPLE_part3.tga", "./output/part3.tga");

    /*** TASK 4
     * Multiply “layer2.tga” with “circles.tga”, and store it.
     * Load “pattern2.tga” and, using that as the top layer,
     * combine it with the previous result using the Subtract blending mode.
     ***/

    // load the layer2.tga file
    Header layerTwoHeader2;
    vector<pixel> layerTwoVector2;
    parseInFile("./input/layer2.tga", layerTwoHeader2, layerTwoVector2);

    // load the circles.tga file
    Header circlesHeader;
    vector<pixel> circlesVector;
    parseInFile("./input/circles.tga", circlesHeader, circlesVector);

    vector<pixel> partFourVector = taskOne(layerTwoVector2, circlesVector);

    // load the pattern2.tga file
    Header patternTwoHeader2;
    vector<pixel> patternTwoVector2;
    parseInFile("./input/pattern2.tga", patternTwoHeader2, patternTwoVector2);

    // use patternTwoVector2. subtract from partFourVector
    vector<pixel> subtractedVector = taskTwo(patternTwoVector2, partFourVector);

    createNewFile("./output/part4.tga", patternTwoHeader2,subtractedVector);

    imageTest("./examples/EXAMPLE_part4.tga", "./output/part4.tga");

    /*** TASK 5
     * Combine “layer1.tga” (as the top layer) with “pattern1.tga” using the Overlay blending mode.
     ***/

    Header layerOneHeader3;
    vector<pixel> layerOneVector3;
    parseInFile("./input/layer1.tga", layerOneHeader3, layerOneVector3);

    // load the pattern1.tga file
    Header patternOneHeader2;
    vector<pixel> patternOneVector2;
    parseInFile("./input/pattern1.tga", patternOneHeader2, patternOneVector2);

    vector<pixel> partFiveVector = taskFive(layerOneVector3, patternOneVector2);

    createNewFile("./output/part5.tga", layerOneHeader3,partFiveVector);

    imageTest("./examples/EXAMPLE_part5.tga", "./output/part5.tga");

    /*** TASK 6
     * Load “car.tga” and add 200 to the green channel.
     ***/

    // load the car.tga file
    Header carHeader2;
    vector<pixel> carvector2;
    parseInFile("./input/car.tga", carHeader2, carvector2);

    vector<pixel> greenTransform = taskSix(carvector2);

    createNewFile("./output/part6.tga", carHeader2,greenTransform);

    imageTest("./examples/EXAMPLE_part6.tga", "./output/part6.tga");

    /*** TASK 7
     * Load “car.tga” and scale (multiply) the red channel by 4, and the blue channel by 0. This will
     increase the intensity of any red in the image, while negating any blue it may have.
     */

    // load the car.tga file
    Header carHeader3;
    vector<pixel> carvector3;
    parseInFile("./input/car.tga", carHeader3, carvector3);

    vector<pixel> paintJobVector = taskSeven(carvector3);

    createNewFile("./output/part7.tga", carHeader3,paintJobVector);

    imageTest("./examples/EXAMPLE_part7.tga", "./output/part7.tga");

    /*** TASK 8
     * Load “car.tga” and write each channel to a separate file:
     * the red channel should be “part8_r.tga”,
     * the green channel should be “part8_g.tga”,
     * and the blue channel should be “part8_b.tga”
 (Hint: If your red channel image appears all red, try writing [Red, Red, Red] instead of [Red, 0, 0] to the file—ditto for green and blue!)
  ***/

    // load the car.tga file
    Header carHeader4;
    vector<pixel> carvector4;
    parseInFile("./input/car.tga", carHeader4, carvector4);

    vector<pixel> modifiedImage;
    modifiedImage = taskEight("red", carvector4);
    createNewFile("./output/part8_r.tga", carHeader4,modifiedImage);
    imageTest("./examples/EXAMPLE_part8_r.tga", "./output/part8_r.tga");

    modifiedImage = taskEight("blue", carvector4);
    createNewFile("./output/part8_b.tga", carHeader4,modifiedImage);
    imageTest("./examples/EXAMPLE_part8_b.tga", "./output/part8_b.tga");

    modifiedImage = taskEight("green", carvector4);
    createNewFile("./output/part8_g.tga", carHeader4,modifiedImage);
    imageTest("./examples/EXAMPLE_part8_g.tga", "./output/part8_g.tga");

    /*** TASK 9
     * Load “layer_red.tga”, “layer_green.tga” and “layer_blue.tga”, and combine the three files into one file.
     * The data from “layer_red.tga” is the red channel of the new image, layer_green is green, and layer_blue is blue.
     */

    Header redLayerHeader;
    vector<pixel> redLayerVector;
    parseInFile("./input/layer_red.tga", redLayerHeader, redLayerVector);

    Header blueLayerHeader;
    vector<pixel> blueLayerVector;
    parseInFile("./input/layer_blue.tga", blueLayerHeader, blueLayerVector);

    Header greenLayerHeader;
    vector<pixel> greenLayerVector;
    parseInFile("./input/layer_green.tga", greenLayerHeader, greenLayerVector);

    vector<pixel> partNine = taskNine(redLayerVector, blueLayerVector, greenLayerVector);

    createNewFile("./output/part9.tga", redLayerHeader,partNine);
    imageTest("./examples/EXAMPLE_part9.tga", "./output/part9.tga");

    /*** TASK 10
     *  Load “text2.tga”, and rotate it 180 degrees, flipping it upside down.
     *  This is easier than you think! Try diagramming the data of an image (such as earlier in this document).
     *  What would the data look like if you flipped it? Now, how to write some code to accomplish that...?
     * ***/

    // read the file and get its vector
    Header text2Header;
    vector<pixel> text2Vector;
    parseInFile("./input/text2.tga", text2Header, text2Vector);

    std::reverse(text2Vector.begin(), text2Vector.end());

    createNewFile("./output/part10.tga", text2Header,text2Vector);
    imageTest("./examples/EXAMPLE_part10.tga", "./output/part10.tga");

    return 0;
}