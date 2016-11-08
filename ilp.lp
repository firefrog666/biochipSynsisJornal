Minimize
 + ex0y0s1t0U + ex0y0s0t1U + ex0y1s1t1U + ex0y1s0t2U + ex0y2s1t2U + ex0y2s0t3U + ex0y3s1t3U + ex1y0s2t0U + ex1y0s1t1U + ex1y1s2t1U + ex1y1s1t2U + ex1y2s2t2U + ex1y2s1t3U + ex1y3s2t3U + ex2y0s3t0U + ex2y0s2t1U + ex2y1s3t1U + ex2y1s2t2U + ex2y2s3t2U + ex2y2s2t3U + ex2y3s3t3U + ex3y0s3t1U + ex3y1s3t2U + ex3y2s3t3U
SUBJECT TO
 + d1Bindnx0y0 + d1Bindnx0y1 + d1Bindnx0y2 + d1Bindnx0y3 + d1Bindnx1y0 + d1Bindnx1y1 + d1Bindnx1y2 + d1Bindnx1y3 + d1Bindnx2y0 + d1Bindnx2y1 + d1Bindnx2y2 + d1Bindnx2y3 + d1Bindnx3y0 + d1Bindnx3y1 + d1Bindnx3y2 + d1Bindnx3y3 = 1
 + d3Bindnx0y0 + d3Bindnx0y1 + d3Bindnx0y2 + d3Bindnx0y3 + d3Bindnx1y0 + d3Bindnx1y1 + d3Bindnx1y2 + d3Bindnx1y3 + d3Bindnx2y0 + d3Bindnx2y1 + d3Bindnx2y2 + d3Bindnx2y3 + d3Bindnx3y0 + d3Bindnx3y1 + d3Bindnx3y2 + d3Bindnx3y3 = 1
 + d1Bindnx0y0 + d3Bindnx0y0 <= 1
 + d1Bindnx0y1 + d3Bindnx0y1 <= 1
 + d1Bindnx0y2 + d3Bindnx0y2 <= 1
 + d1Bindnx0y3 + d3Bindnx0y3 <= 1
 + d1Bindnx1y0 + d3Bindnx1y0 <= 1
 + d1Bindnx1y1 + d3Bindnx1y1 <= 1
 + d1Bindnx1y2 + d3Bindnx1y2 <= 1
 + d1Bindnx1y3 + d3Bindnx1y3 <= 1
 + d1Bindnx2y0 + d3Bindnx2y0 <= 1
 + d1Bindnx2y1 + d3Bindnx2y1 <= 1
 + d1Bindnx2y2 + d3Bindnx2y2 <= 1
 + d1Bindnx2y3 + d3Bindnx2y3 <= 1
 + d1Bindnx3y0 + d3Bindnx3y0 <= 1
 + d1Bindnx3y1 + d3Bindnx3y1 <= 1
 + d1Bindnx3y2 + d3Bindnx3y2 <= 1
 + d1Bindnx3y3 + d3Bindnx3y3 <= 1
 + co1o2Uex0y0s1t0 + co1o2Uex0y0s0t1 + co1o2Uex0y1s1t1 + co1o2Uex0y1s0t2 + co1o2Uex0y2s1t2 + co1o2Uex0y2s0t3 + co1o2Uex0y3s1t3 + co1o2Uex1y0s2t0 + co1o2Uex1y0s1t1 + co1o2Uex1y1s2t1 + co1o2Uex1y1s1t2 + co1o2Uex1y2s2t2 + co1o2Uex1y2s1t3 + co1o2Uex1y3s2t3 + co1o2Uex2y0s3t0 + co1o2Uex2y0s2t1 + co1o2Uex2y1s3t1 + co1o2Uex2y1s2t2 + co1o2Uex2y2s3t2 + co1o2Uex2y2s2t3 + co1o2Uex2y3s3t3 + co1o2Uex3y0s3t1 + co1o2Uex3y1s3t2 + co1o2Uex3y2s3t3 >= 1
 + co1o2Uex0y0s1t0 + co1o2Uex0y0s0t1 - 10000 d1Bindnx0y0 >= -9999
 + co1o2Uex0y0s1t0 + co1o2Uex0y0s0t1 + 10000 d1Bindnx0y0 <= 10001
 + co1o2Uex0y0s1t0 + co1o2Uex0y0s0t1 - 10000 d3Bindnx0y0 >= -9999
 + co1o2Uex0y0s1t0 + co1o2Uex0y0s0t1 + 10000 d3Bindnx0y0 <= 10001
 + co1o2Uex0y0s0t1 + co1o2Uex0y1s1t1 + co1o2Uex0y1s0t2 - 10000 d1Bindnx0y1 >= -9999
 + co1o2Uex0y0s0t1 + co1o2Uex0y1s1t1 + co1o2Uex0y1s0t2 + 10000 d1Bindnx0y1 <= 10001
 + co1o2Uex0y0s0t1 + co1o2Uex0y1s1t1 + co1o2Uex0y1s0t2 - 10000 d3Bindnx0y1 >= -9999
 + co1o2Uex0y0s0t1 + co1o2Uex0y1s1t1 + co1o2Uex0y1s0t2 + 10000 d3Bindnx0y1 <= 10001
 + co1o2Uex0y1s0t2 + co1o2Uex0y2s1t2 + co1o2Uex0y2s0t3 - 10000 d1Bindnx0y2 >= -9999
 + co1o2Uex0y1s0t2 + co1o2Uex0y2s1t2 + co1o2Uex0y2s0t3 + 10000 d1Bindnx0y2 <= 10001
 + co1o2Uex0y1s0t2 + co1o2Uex0y2s1t2 + co1o2Uex0y2s0t3 - 10000 d3Bindnx0y2 >= -9999
 + co1o2Uex0y1s0t2 + co1o2Uex0y2s1t2 + co1o2Uex0y2s0t3 + 10000 d3Bindnx0y2 <= 10001
 + co1o2Uex0y2s0t3 + co1o2Uex0y3s1t3 - 10000 d1Bindnx0y3 >= -9999
 + co1o2Uex0y2s0t3 + co1o2Uex0y3s1t3 + 10000 d1Bindnx0y3 <= 10001
 + co1o2Uex0y2s0t3 + co1o2Uex0y3s1t3 - 10000 d3Bindnx0y3 >= -9999
 + co1o2Uex0y2s0t3 + co1o2Uex0y3s1t3 + 10000 d3Bindnx0y3 <= 10001
 + co1o2Uex0y0s1t0 + co1o2Uex1y0s2t0 + co1o2Uex1y0s1t1 - 10000 d1Bindnx1y0 >= -9999
 + co1o2Uex0y0s1t0 + co1o2Uex1y0s2t0 + co1o2Uex1y0s1t1 + 10000 d1Bindnx1y0 <= 10001
 + co1o2Uex0y0s1t0 + co1o2Uex1y0s2t0 + co1o2Uex1y0s1t1 - 10000 d3Bindnx1y0 >= -9999
 + co1o2Uex0y0s1t0 + co1o2Uex1y0s2t0 + co1o2Uex1y0s1t1 + 10000 d3Bindnx1y0 <= 10001
 + co1o2Uex0y1s1t1 + co1o2Uex1y0s1t1 + co1o2Uex1y1s2t1 + co1o2Uex1y1s1t2 - 10000 d1Bindnx1y1 >= -9999
 + co1o2Uex0y1s1t1 + co1o2Uex1y0s1t1 + co1o2Uex1y1s2t1 + co1o2Uex1y1s1t2 + 10000 d1Bindnx1y1 <= 10001
 + co1o2Uex0y1s1t1 + co1o2Uex1y0s1t1 + co1o2Uex1y1s2t1 + co1o2Uex1y1s1t2 - 10000 d3Bindnx1y1 >= -9999
 + co1o2Uex0y1s1t1 + co1o2Uex1y0s1t1 + co1o2Uex1y1s2t1 + co1o2Uex1y1s1t2 + 10000 d3Bindnx1y1 <= 10001
 + co1o2Uex0y2s1t2 + co1o2Uex1y1s1t2 + co1o2Uex1y2s2t2 + co1o2Uex1y2s1t3 - 10000 d1Bindnx1y2 >= -9999
 + co1o2Uex0y2s1t2 + co1o2Uex1y1s1t2 + co1o2Uex1y2s2t2 + co1o2Uex1y2s1t3 + 10000 d1Bindnx1y2 <= 10001
 + co1o2Uex0y2s1t2 + co1o2Uex1y1s1t2 + co1o2Uex1y2s2t2 + co1o2Uex1y2s1t3 - 10000 d3Bindnx1y2 >= -9999
 + co1o2Uex0y2s1t2 + co1o2Uex1y1s1t2 + co1o2Uex1y2s2t2 + co1o2Uex1y2s1t3 + 10000 d3Bindnx1y2 <= 10001
 + co1o2Uex0y3s1t3 + co1o2Uex1y2s1t3 + co1o2Uex1y3s2t3 - 10000 d1Bindnx1y3 >= -9999
 + co1o2Uex0y3s1t3 + co1o2Uex1y2s1t3 + co1o2Uex1y3s2t3 + 10000 d1Bindnx1y3 <= 10001
 + co1o2Uex0y3s1t3 + co1o2Uex1y2s1t3 + co1o2Uex1y3s2t3 - 10000 d3Bindnx1y3 >= -9999
 + co1o2Uex0y3s1t3 + co1o2Uex1y2s1t3 + co1o2Uex1y3s2t3 + 10000 d3Bindnx1y3 <= 10001
 + co1o2Uex1y0s2t0 + co1o2Uex2y0s3t0 + co1o2Uex2y0s2t1 - 10000 d1Bindnx2y0 >= -9999
 + co1o2Uex1y0s2t0 + co1o2Uex2y0s3t0 + co1o2Uex2y0s2t1 + 10000 d1Bindnx2y0 <= 10001
 + co1o2Uex1y0s2t0 + co1o2Uex2y0s3t0 + co1o2Uex2y0s2t1 - 10000 d3Bindnx2y0 >= -9999
 + co1o2Uex1y0s2t0 + co1o2Uex2y0s3t0 + co1o2Uex2y0s2t1 + 10000 d3Bindnx2y0 <= 10001
 + co1o2Uex1y1s2t1 + co1o2Uex2y0s2t1 + co1o2Uex2y1s3t1 + co1o2Uex2y1s2t2 - 10000 d1Bindnx2y1 >= -9999
 + co1o2Uex1y1s2t1 + co1o2Uex2y0s2t1 + co1o2Uex2y1s3t1 + co1o2Uex2y1s2t2 + 10000 d1Bindnx2y1 <= 10001
 + co1o2Uex1y1s2t1 + co1o2Uex2y0s2t1 + co1o2Uex2y1s3t1 + co1o2Uex2y1s2t2 - 10000 d3Bindnx2y1 >= -9999
 + co1o2Uex1y1s2t1 + co1o2Uex2y0s2t1 + co1o2Uex2y1s3t1 + co1o2Uex2y1s2t2 + 10000 d3Bindnx2y1 <= 10001
 + co1o2Uex1y2s2t2 + co1o2Uex2y1s2t2 + co1o2Uex2y2s3t2 + co1o2Uex2y2s2t3 - 10000 d1Bindnx2y2 >= -9999
 + co1o2Uex1y2s2t2 + co1o2Uex2y1s2t2 + co1o2Uex2y2s3t2 + co1o2Uex2y2s2t3 + 10000 d1Bindnx2y2 <= 10001
 + co1o2Uex1y2s2t2 + co1o2Uex2y1s2t2 + co1o2Uex2y2s3t2 + co1o2Uex2y2s2t3 - 10000 d3Bindnx2y2 >= -9999
 + co1o2Uex1y2s2t2 + co1o2Uex2y1s2t2 + co1o2Uex2y2s3t2 + co1o2Uex2y2s2t3 + 10000 d3Bindnx2y2 <= 10001
 + co1o2Uex1y3s2t3 + co1o2Uex2y2s2t3 + co1o2Uex2y3s3t3 - 10000 d1Bindnx2y3 >= -9999
 + co1o2Uex1y3s2t3 + co1o2Uex2y2s2t3 + co1o2Uex2y3s3t3 + 10000 d1Bindnx2y3 <= 10001
 + co1o2Uex1y3s2t3 + co1o2Uex2y2s2t3 + co1o2Uex2y3s3t3 - 10000 d3Bindnx2y3 >= -9999
 + co1o2Uex1y3s2t3 + co1o2Uex2y2s2t3 + co1o2Uex2y3s3t3 + 10000 d3Bindnx2y3 <= 10001
 + co1o2Uex2y0s3t0 + co1o2Uex3y0s3t1 - 10000 d1Bindnx3y0 >= -9999
 + co1o2Uex2y0s3t0 + co1o2Uex3y0s3t1 + 10000 d1Bindnx3y0 <= 10001
 + co1o2Uex2y0s3t0 + co1o2Uex3y0s3t1 - 10000 d3Bindnx3y0 >= -9999
 + co1o2Uex2y0s3t0 + co1o2Uex3y0s3t1 + 10000 d3Bindnx3y0 <= 10001
 + co1o2Uex2y1s3t1 + co1o2Uex3y0s3t1 + co1o2Uex3y1s3t2 - 10000 d1Bindnx3y1 >= -9999
 + co1o2Uex2y1s3t1 + co1o2Uex3y0s3t1 + co1o2Uex3y1s3t2 + 10000 d1Bindnx3y1 <= 10001
 + co1o2Uex2y1s3t1 + co1o2Uex3y0s3t1 + co1o2Uex3y1s3t2 - 10000 d3Bindnx3y1 >= -9999
 + co1o2Uex2y1s3t1 + co1o2Uex3y0s3t1 + co1o2Uex3y1s3t2 + 10000 d3Bindnx3y1 <= 10001
 + co1o2Uex2y2s3t2 + co1o2Uex3y1s3t2 + co1o2Uex3y2s3t3 - 10000 d1Bindnx3y2 >= -9999
 + co1o2Uex2y2s3t2 + co1o2Uex3y1s3t2 + co1o2Uex3y2s3t3 + 10000 d1Bindnx3y2 <= 10001
 + co1o2Uex2y2s3t2 + co1o2Uex3y1s3t2 + co1o2Uex3y2s3t3 - 10000 d3Bindnx3y2 >= -9999
 + co1o2Uex2y2s3t2 + co1o2Uex3y1s3t2 + co1o2Uex3y2s3t3 + 10000 d3Bindnx3y2 <= 10001
 + co1o2Uex2y3s3t3 + co1o2Uex3y2s3t3 - 10000 d1Bindnx3y3 >= -9999
 + co1o2Uex2y3s3t3 + co1o2Uex3y2s3t3 + 10000 d1Bindnx3y3 <= 10001
 + co1o2Uex2y3s3t3 + co1o2Uex3y2s3t3 - 10000 d3Bindnx3y3 >= -9999
 + co1o2Uex2y3s3t3 + co1o2Uex3y2s3t3 + 10000 d3Bindnx3y3 <= 10001
 + co1o2Uex0y0s1t0 + co1o2Uex0y0s0t1 - 2 co1o2Unx0y0 + 10000 d1Bindnx0y0 + 10000 d3Bindnx0y0 >= 0
 + co1o2Uex0y0s1t0 + co1o2Uex0y0s0t1 - 2 co1o2Unx0y0 - 10000 d1Bindnx0y0 - 10000 d3Bindnx0y0 <= 0
 + co1o2Uex0y0s0t1 + co1o2Uex0y1s1t1 + co1o2Uex0y1s0t2 - 2 co1o2Unx0y1 + 10000 d1Bindnx0y1 + 10000 d3Bindnx0y1 >= 0
 + co1o2Uex0y0s0t1 + co1o2Uex0y1s1t1 + co1o2Uex0y1s0t2 - 2 co1o2Unx0y1 - 10000 d1Bindnx0y1 - 10000 d3Bindnx0y1 <= 0
 + co1o2Uex0y1s0t2 + co1o2Uex0y2s1t2 + co1o2Uex0y2s0t3 - 2 co1o2Unx0y2 + 10000 d1Bindnx0y2 + 10000 d3Bindnx0y2 >= 0
 + co1o2Uex0y1s0t2 + co1o2Uex0y2s1t2 + co1o2Uex0y2s0t3 - 2 co1o2Unx0y2 - 10000 d1Bindnx0y2 - 10000 d3Bindnx0y2 <= 0
 + co1o2Uex0y2s0t3 + co1o2Uex0y3s1t3 - 2 co1o2Unx0y3 + 10000 d1Bindnx0y3 + 10000 d3Bindnx0y3 >= 0
 + co1o2Uex0y2s0t3 + co1o2Uex0y3s1t3 - 2 co1o2Unx0y3 - 10000 d1Bindnx0y3 - 10000 d3Bindnx0y3 <= 0
 + co1o2Uex0y0s1t0 + co1o2Uex1y0s2t0 + co1o2Uex1y0s1t1 - 2 co1o2Unx1y0 + 10000 d1Bindnx1y0 + 10000 d3Bindnx1y0 >= 0
 + co1o2Uex0y0s1t0 + co1o2Uex1y0s2t0 + co1o2Uex1y0s1t1 - 2 co1o2Unx1y0 - 10000 d1Bindnx1y0 - 10000 d3Bindnx1y0 <= 0
 + co1o2Uex0y1s1t1 + co1o2Uex1y0s1t1 + co1o2Uex1y1s2t1 + co1o2Uex1y1s1t2 - 2 co1o2Unx1y1 + 10000 d1Bindnx1y1 + 10000 d3Bindnx1y1 >= 0
 + co1o2Uex0y1s1t1 + co1o2Uex1y0s1t1 + co1o2Uex1y1s2t1 + co1o2Uex1y1s1t2 - 2 co1o2Unx1y1 - 10000 d1Bindnx1y1 - 10000 d3Bindnx1y1 <= 0
 + co1o2Uex0y2s1t2 + co1o2Uex1y1s1t2 + co1o2Uex1y2s2t2 + co1o2Uex1y2s1t3 - 2 co1o2Unx1y2 + 10000 d1Bindnx1y2 + 10000 d3Bindnx1y2 >= 0
 + co1o2Uex0y2s1t2 + co1o2Uex1y1s1t2 + co1o2Uex1y2s2t2 + co1o2Uex1y2s1t3 - 2 co1o2Unx1y2 - 10000 d1Bindnx1y2 - 10000 d3Bindnx1y2 <= 0
 + co1o2Uex0y3s1t3 + co1o2Uex1y2s1t3 + co1o2Uex1y3s2t3 - 2 co1o2Unx1y3 + 10000 d1Bindnx1y3 + 10000 d3Bindnx1y3 >= 0
 + co1o2Uex0y3s1t3 + co1o2Uex1y2s1t3 + co1o2Uex1y3s2t3 - 2 co1o2Unx1y3 - 10000 d1Bindnx1y3 - 10000 d3Bindnx1y3 <= 0
 + co1o2Uex1y0s2t0 + co1o2Uex2y0s3t0 + co1o2Uex2y0s2t1 - 2 co1o2Unx2y0 + 10000 d1Bindnx2y0 + 10000 d3Bindnx2y0 >= 0
 + co1o2Uex1y0s2t0 + co1o2Uex2y0s3t0 + co1o2Uex2y0s2t1 - 2 co1o2Unx2y0 - 10000 d1Bindnx2y0 - 10000 d3Bindnx2y0 <= 0
 + co1o2Uex1y1s2t1 + co1o2Uex2y0s2t1 + co1o2Uex2y1s3t1 + co1o2Uex2y1s2t2 - 2 co1o2Unx2y1 + 10000 d1Bindnx2y1 + 10000 d3Bindnx2y1 >= 0
 + co1o2Uex1y1s2t1 + co1o2Uex2y0s2t1 + co1o2Uex2y1s3t1 + co1o2Uex2y1s2t2 - 2 co1o2Unx2y1 - 10000 d1Bindnx2y1 - 10000 d3Bindnx2y1 <= 0
 + co1o2Uex1y2s2t2 + co1o2Uex2y1s2t2 + co1o2Uex2y2s3t2 + co1o2Uex2y2s2t3 - 2 co1o2Unx2y2 + 10000 d1Bindnx2y2 + 10000 d3Bindnx2y2 >= 0
 + co1o2Uex1y2s2t2 + co1o2Uex2y1s2t2 + co1o2Uex2y2s3t2 + co1o2Uex2y2s2t3 - 2 co1o2Unx2y2 - 10000 d1Bindnx2y2 - 10000 d3Bindnx2y2 <= 0
 + co1o2Uex1y3s2t3 + co1o2Uex2y2s2t3 + co1o2Uex2y3s3t3 - 2 co1o2Unx2y3 + 10000 d1Bindnx2y3 + 10000 d3Bindnx2y3 >= 0
 + co1o2Uex1y3s2t3 + co1o2Uex2y2s2t3 + co1o2Uex2y3s3t3 - 2 co1o2Unx2y3 - 10000 d1Bindnx2y3 - 10000 d3Bindnx2y3 <= 0
 + co1o2Uex2y0s3t0 + co1o2Uex3y0s3t1 - 2 co1o2Unx3y0 + 10000 d1Bindnx3y0 + 10000 d3Bindnx3y0 >= 0
 + co1o2Uex2y0s3t0 + co1o2Uex3y0s3t1 - 2 co1o2Unx3y0 - 10000 d1Bindnx3y0 - 10000 d3Bindnx3y0 <= 0
 + co1o2Uex2y1s3t1 + co1o2Uex3y0s3t1 + co1o2Uex3y1s3t2 - 2 co1o2Unx3y1 + 10000 d1Bindnx3y1 + 10000 d3Bindnx3y1 >= 0
 + co1o2Uex2y1s3t1 + co1o2Uex3y0s3t1 + co1o2Uex3y1s3t2 - 2 co1o2Unx3y1 - 10000 d1Bindnx3y1 - 10000 d3Bindnx3y1 <= 0
 + co1o2Uex2y2s3t2 + co1o2Uex3y1s3t2 + co1o2Uex3y2s3t3 - 2 co1o2Unx3y2 + 10000 d1Bindnx3y2 + 10000 d3Bindnx3y2 >= 0
 + co1o2Uex2y2s3t2 + co1o2Uex3y1s3t2 + co1o2Uex3y2s3t3 - 2 co1o2Unx3y2 - 10000 d1Bindnx3y2 - 10000 d3Bindnx3y2 <= 0
 + co1o2Uex2y3s3t3 + co1o2Uex3y2s3t3 - 2 co1o2Unx3y3 + 10000 d1Bindnx3y3 + 10000 d3Bindnx3y3 >= 0
 + co1o2Uex2y3s3t3 + co1o2Uex3y2s3t3 - 2 co1o2Unx3y3 - 10000 d1Bindnx3y3 - 10000 d3Bindnx3y3 <= 0
 + co1o2Uex0y0s1t0 - 10000 ex0y0s1t0U <= 0
 + co1o2Uex0y0s0t1 - 10000 ex0y0s0t1U <= 0
 + co1o2Uex0y1s1t1 - 10000 ex0y1s1t1U <= 0
 + co1o2Uex0y1s0t2 - 10000 ex0y1s0t2U <= 0
 + co1o2Uex0y2s1t2 - 10000 ex0y2s1t2U <= 0
 + co1o2Uex0y2s0t3 - 10000 ex0y2s0t3U <= 0
 + co1o2Uex0y3s1t3 - 10000 ex0y3s1t3U <= 0
 + co1o2Uex1y0s2t0 - 10000 ex1y0s2t0U <= 0
 + co1o2Uex1y0s1t1 - 10000 ex1y0s1t1U <= 0
 + co1o2Uex1y1s2t1 - 10000 ex1y1s2t1U <= 0
 + co1o2Uex1y1s1t2 - 10000 ex1y1s1t2U <= 0
 + co1o2Uex1y2s2t2 - 10000 ex1y2s2t2U <= 0
 + co1o2Uex1y2s1t3 - 10000 ex1y2s1t3U <= 0
 + co1o2Uex1y3s2t3 - 10000 ex1y3s2t3U <= 0
 + co1o2Uex2y0s3t0 - 10000 ex2y0s3t0U <= 0
 + co1o2Uex2y0s2t1 - 10000 ex2y0s2t1U <= 0
 + co1o2Uex2y1s3t1 - 10000 ex2y1s3t1U <= 0
 + co1o2Uex2y1s2t2 - 10000 ex2y1s2t2U <= 0
 + co1o2Uex2y2s3t2 - 10000 ex2y2s3t2U <= 0
 + co1o2Uex2y2s2t3 - 10000 ex2y2s2t3U <= 0
 + co1o2Uex2y3s3t3 - 10000 ex2y3s3t3U <= 0
 + co1o2Uex3y0s3t1 - 10000 ex3y0s3t1U <= 0
 + co1o2Uex3y1s3t2 - 10000 ex3y1s3t2U <= 0
 + co1o2Uex3y2s3t3 - 10000 ex3y2s3t3U <= 0
 
Binaries
d1Bindnx0y0
d1Bindnx0y1
d1Bindnx0y2
d1Bindnx0y3
d1Bindnx1y0
d1Bindnx1y1
d1Bindnx1y2
d1Bindnx1y3
d1Bindnx2y0
d1Bindnx2y1
d1Bindnx2y2
d1Bindnx2y3
d1Bindnx3y0
d1Bindnx3y1
d1Bindnx3y2
d1Bindnx3y3
d3Bindnx0y0
d3Bindnx0y1
d3Bindnx0y2
d3Bindnx0y3
d3Bindnx1y0
d3Bindnx1y1
d3Bindnx1y2
d3Bindnx1y3
d3Bindnx2y0
d3Bindnx2y1
d3Bindnx2y2
d3Bindnx2y3
d3Bindnx3y0
d3Bindnx3y1
d3Bindnx3y2
d3Bindnx3y3
co1o2Uex0y0s1t0
co1o2Uex0y0s0t1
co1o2Uex0y1s1t1
co1o2Uex0y1s0t2
co1o2Uex0y2s1t2
co1o2Uex0y2s0t3
co1o2Uex0y3s1t3
co1o2Uex1y0s2t0
co1o2Uex1y0s1t1
co1o2Uex1y1s2t1
co1o2Uex1y1s1t2
co1o2Uex1y2s2t2
co1o2Uex1y2s1t3
co1o2Uex1y3s2t3
co1o2Uex2y0s3t0
co1o2Uex2y0s2t1
co1o2Uex2y1s3t1
co1o2Uex2y1s2t2
co1o2Uex2y2s3t2
co1o2Uex2y2s2t3
co1o2Uex2y3s3t3
co1o2Uex3y0s3t1
co1o2Uex3y1s3t2
co1o2Uex3y2s3t3
co1o2Unx0y0
co1o2Unx0y1
co1o2Unx0y2
co1o2Unx0y3
co1o2Unx1y0
co1o2Unx1y1
co1o2Unx1y2
co1o2Unx1y3
co1o2Unx2y0
co1o2Unx2y1
co1o2Unx2y2
co1o2Unx2y3
co1o2Unx3y0
co1o2Unx3y1
co1o2Unx3y2
co1o2Unx3y3
ex0y0s1t0U
ex0y0s0t1U
ex0y1s1t1U
ex0y1s0t2U
ex0y2s1t2U
ex0y2s0t3U
ex0y3s1t3U
ex1y0s2t0U
ex1y0s1t1U
ex1y1s2t1U
ex1y1s1t2U
ex1y2s2t2U
ex1y2s1t3U
ex1y3s2t3U
ex2y0s3t0U
ex2y0s2t1U
ex2y1s3t1U
ex2y1s2t2U
ex2y2s3t2U
ex2y2s2t3U
ex2y3s3t3U
ex3y0s3t1U
ex3y1s3t2U
ex3y2s3t3U
