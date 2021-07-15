Top Reconstruction Analysis Code
===============
In this github page you can find the files used by the Uniandes Pheno Group for the analysis of t tbar Zprime signals and its corresponding Standard Model backgrounds using MadAnalysis. 
There are two levels for the analysis:

1. Analysis at Madgraph level (Files in Madanalysis_level folder).
2. Analysis at Delphes level (Files in Delphes_level folder).

In each folder, you will find the .h and .cpp files (mandatory for run MadAnalysis) as well as a bash script (execute_all.sh). 

The .h and .cpp files 
---------
These are the files that must be inside the Analysis_Folder/Build/SampleAnalyzer/User/Analyzer/ folder created by MadAnalysis, where "Analysis_Folder" is the name of the folder created automatically via MadAnalysis Expert Mode. At Madgraph level, please set Analysis_Folder = Prueba and, at Delphes level, Analysis_Folder = Prueba_Delphes. Please DO NOT change the name of the .h and .cpp files. 

Bash File (execute_all.sh)
---------
The bash script allows to run Madnalysis over the signals and backgrounds specified in the .sh file. The paths of the signals and backgrounds must be in the form: common_path + signal_i + extension, where "common_path" is the path where all the signals and backgrounds are, "signal_i" is the name of the i-th folder asocciated with some signal or background called "signal" and "extension" is the complement of the common_path + signal_i path. As an example, suppose that you have two backgrounds (ttbarh and ttbarbbar) at Delphes level, separated in 60 and 90 folders respectively. The paths to the .root files are:

1. For ttbarh: /disco3/SIMULACIONES/with_delphes/ttbarh_i/Events/run_01/tag_1_delphes_events.root
2. For ttbarbbar: /disco3/SIMULACIONES/with_delphes/ttbarbbar_j/Events/run_01/tag_1_delphes_events.root

where 1<i<60 and 1<j<90. Then you have to set:

* signals=("ttbarh" "ttbarbbar")
* jobs=(60 90)
* extension="/Events/run_01/tag_1_delphes_events.root"
* common_path="/disco3/SIMULACIONES/with_delphes/"


How to run the analysis code in MadAnalysis
---------
1. Move to Analysis_Folder/Build folder
2. source setup.sh 
3. make 
4. ./execute_all.sh OR  nohup ./execute_all.sh & (to run the process in second plane)


Results
---------
After the execution of the analysis code, some .root files are generated with the histograms produced by the analysis code. There are as many .root files as signals and backgrounds defined in the bash file. For example, if signals=("ttbarh" "ttbarbbar") in the bash file, then the files ttbarh.root and ttbarbbar.root files will be generated afther the execution of the analysis code. 

Joining the results
---------
In addition to the analysis code, there is a file that joins all the results obtained in a single file (a single histogram for each kinetic variable). This file is called merge_histos.cxx. The only thing to keep in mind is that you only have to change three variables in the code: "names_files", "names_files_wo_ext" and "names", in order to join the .root files specified in these variables. "names_files" contains the names of the .root files that you will join. "names_files_wo_text" contains the names of the signals and backgrounds (in the same order as in "names_files") but in a LaTeX format (the backslash is changed by a double backslash). "names" contains the names of the signals and backgrounds (in the same order as in "names_files") in a LaTeX format, but the backslash is changed for # and the $ simbols dissapear. For example, if signals=("ttbarh" "ttbarbbar"), then:

* vector<std::string> names_files {"ttbarh.root", "ttbarbbar.root"};
* vector<std::string> names_files_wo_ext {"$t\\bar{t}h$", "$t\\bar{t}b\\bar{b}$"};
* vector<std::string> names {"t#bar{t}h", "t#bar{t}b#bar{b}"};

Once the code has been modified, you have to run the code via root, with the command: root -q merge_histos.cxx. The resulting file will be called "joined.root"


Developers
---------
* Manuel Fernando Sánchez Alarcón. Personal Webpage: https://spoksonat.github.io/Personal_Webpage/

Enjoy,

Manuel Fernando Sánchez Alarcón.
