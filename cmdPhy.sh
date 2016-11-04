#/bin/sh

#cp ~/Research/TCAD16_RFPandR/Prog/rfpandr_result/drawPhy_c$1_p$2_i$3.txt .
echo $1.txt | asy -o drawPhy.eps drawPhy.asy && epspdf drawPhy.eps
evince drawPhy.pdf
# open "drawPhy_c$1_p$2_i$3.pdf"
