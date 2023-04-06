# import the necessary packages
# pip install --upgrade imutils
from imutils.object_detection import non_max_suppression
import numpy as np
import argparse
import time
import cv2
# construct the argument parser and parse the arguments

# https://pyimagesearch.com/2018/08/20/opencv-text-detection-east-text-detector/#pyis-cta-modal
image_path = '1.jpg'

# load the input image and grab the image dimensions
image = cv2.imread(image_path)
orig = image.copy()
(H, W) = image.shape[:2]

# define the two output layer names for the EAST detector model that
# we are interested -- the first is the output probabilities and the
# second can be used to derive the bounding box coordinates of text
layerNames = [
	"feature_fusion/Conv_7/Sigmoid",
	"feature_fusion/concat_3"]

east = 'path_to_wtf'

# load the pre-trained EAST text detector
print("[INFO] loading EAST text detector...")
net = cv2.dnn.readNet(east)
# construct a blob from the image and then perform a forward pass of
# the model to obtain the two output layer sets
blob = cv2.dnn.blobFromImage(image, 1.0, (W, H),
	(123.68, 116.78, 103.94), swapRB=True, crop=False)
start = time.time()
net.setInput(blob)
(scores, geometry) = net.forward(layerNames)
end = time.time()
# show timing information on text prediction
print("[INFO] text detection took {:.6f} seconds".format(end - start))