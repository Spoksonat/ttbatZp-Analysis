 # Declare an array of string with type
#signals=("ttbarh" "ttbarbbar_noh" "ttbarttbar" "Zprime_bbar_350")
#jobs=(60 3 4 5)
signals=("ttbarh" "ttbarbbar_noh")
jobs=(6 6)
extension="/Events/run_01/tag_1_delphes_events.root"
#common_path="/disco4/SIMULACIONES/from_disco3/with_delphes/"
common_path="/disco3/SIMULACIONES/with_delphes/"

for i in ${!signals[@]}; do 
  rm ${signals[i]}.txt
done
 
for i in ${!signals[@]}; do for j in $(seq 1 ${jobs[$i]}); do 
  echo $common_path${signals[i]}/${signals[i]}_$j$extension >> ${signals[i]}.txt
done
done

for i in ${!signals[@]}; do 
  ./MadAnalysis5job ${signals[i]}.txt
  mv output.root ${signals[i]}.root
done

for i in ${!signals[@]}; do 
  rm ${signals[i]}.txt
done
