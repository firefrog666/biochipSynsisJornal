#/bin/sh

#cp ~/Research/TCAD16_RFPandR/Prog/rfpandr_result/draw_c$1_p$2_i$3.txt .
echo $1.txt | asy -o draw.eps draw.asy && epspdf draw.eps
evince draw.pdf
# open "draw_c$1_p$2_i$3.pdf"
