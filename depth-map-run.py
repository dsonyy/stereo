import stereo as st
import argparse
import cv2 as cv

parser = argparse.ArgumentParser()
parser.add_argument("L", help="left video filename", type=str)
parser.add_argument("R", help="right video filename", type=str)
parser.add_argument("calibration", help="calibration filename", type=str)
args = parser.parse_args()

cameras = st.Cameras([args.L, args.R], transformations=[
    (cv.cvtColor, cv.COLOR_BGR2GRAY),
])
calibration = st.Calibration2Cams()
calibration.load(args.calibration)
stereo = st.StereoVision2Cams(calibration)

stream = st.DepthStream(cameras, stereo, False, False, False)
stream.start()