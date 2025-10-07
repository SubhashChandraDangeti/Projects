## 1. Seam Carving  :

# Problem Statement  
The task is to implement **seam carving** – a content-aware image resizing algorithm that reduces image dimensions by iteratively removing seams of lowest energy. The output should be an image with the desired target width and height.  

# Approach  

1. **Energy Calculation**  
   - Convert image to grayscale using `cv::cvtColor`.  
   - Apply Laplacian filter to detect edges.  
   - Use absolute Laplacian values as pixel energy.  

2. **Seam Identification**  
   - Construct a DP table (energy matrix).  
   - For each pixel `(r, c)`, accumulate the minimum energy from the row above (left, middle, or right).  
   - Identify the minimum energy pixel in the last row and backtrack upwards to mark the seam with `red pixel`.  

3. **Seam Removal**  
   - Mark the seam path with a red pixel.  
   - Remove these red pixels from the image (shifting columns left).  
   - Repeat until the target width/height is reached.  

4. **Handling Horizontal Seams**  
   - Rotate the image by 90° clockwise.  
   - Perform vertical seam removal (same as above).  
   - Rotate back counter-clockwise.  

# Data Structures & Algorithms  
- **Data Structures**:  
  - `cv::Mat` (OpenCV matrix) for image representation.  
  - Dynamic Programming table (`CV_32S` matrix) for storing cumulative energy.  

- **Algorithms**:  
  - Laplacian filter for energy calculation.  
  - Dynamic Programming for seam identification.  
  - Image rotation functions to handle horizontal seam removal.  

# Dependencies  
- I used **OpenCV 4.13.0**  
- C++17 (or later) compiler  

# Compilation  

1. Ensure OpenCV is installed and pkg-config is available.  
2. Make sure you keep sample_input folder in 2025201007_A1 directory 
as I have given imgpath as "sample_input/sample1.jpeg";

# bash
1. g++ SeamCarving.cpp  `pkg-config --cflags --libs opencv4`

2. ./a.out

alternative : /** i used this for execution in cmd line :

1. g++ SeamCarving.cpp  \
    -I/usr/local/include/opencv4 \
    -L/usr/local/lib \
    -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs 
2. ./a.out
    **/
