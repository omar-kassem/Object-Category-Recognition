#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2\features2d\features2d.hpp>
#include <iostream>
#include <stdio.h>
#include <tinydir.h>
#include <opencv2/nonfree/features2d.hpp>
using namespace cv;
using namespace std;

vector<String> getNames(){

	vector<String> names;
	tinydir_dir dir;
	if (tinydir_open(&dir, "C:/Users/Omar/Desktop/Semster 9/CV/TUDarmstadt/PNGImages/motorbike-testset/") == -1)
	{
		perror("Error opening file");
		goto bail;
	}

	while (dir.has_next)
	{
		tinydir_file file;
		if (tinydir_readfile(&dir, &file) == -1)
		{
			perror("Error getting file");
			goto bail;
		}

		names.push_back(file.name);
		if (file.is_dir)
		{
			printf("/");
		}
		printf("\n");

		tinydir_next(&dir);
	}

bail:
	tinydir_close(&dir);
	return names;

}
int main()
{
    vector<String> fileNames=getNames();
	for(int i=0;i<fileNames.size();i++){
		Mat im = imread("C:/Users/Omar/Desktop/Semster 9/CV/TUDarmstadt/PNGImages/motorbike-testset/"+fileNames[i],0);
		Mat dst;
		if (im.empty()) 
		{
			cout << "Cannot load image!" << endl;
		}
		else{
		vector<KeyPoint> points;
		resize(im,dst,Size(300,250),0,0,1);
		equalizeHist( dst, dst );
		Ptr<FeatureDetector> detector(new DenseFeatureDetector(1.f,1,0.1f,5,0,true,false));
		detector->detect(dst,points);
		Mat output;
		//FileStorage fs("image3.sift", FileStorage::WRITE);
		cv::SiftDescriptorExtractor extractor;
		extractor.compute(dst,points,output);
		imwrite(fileNames[i],output);
		/*TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0) 
		KMEANS_RANDOM_CENTER*/
		}
	}
}




