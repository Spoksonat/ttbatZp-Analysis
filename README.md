Top Reconstruction Analysis Code
===============
In this github page you can find the files used by the Uniandes Pheno Group for the analysis of t tbar Zprime signals and its corresponding Standard Model backgrounds using MadAnalysis. 
There are two levels for the analysis:

1. Analysis at Madgraph level (Files in Madanalysis_level folder).
2. Analysis at Delphes level (Files in Delphes_level folder).

In each folder, you will find the .h and .cpp files (mandatory for run MadAnalysis) as well as a bash script (execute_all.sh). 

.h and .cpp files 
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


Download
---------
The latest binaries and source of Doxygen can be downloaded from:
* https://www.doxygen.nl/

Developers
---------
* Linux & Windows and MacOS Build Status: <a href="https://github.com/doxygen/doxygen/actions"><img alt="Github Actions Build Status" src="https://github.com/doxygen/doxygen/workflows/CMake%20Build%20for%20Doxygen/badge.svg"></a>

* Coverity Scan Build Status: <a href="https://scan.coverity.com/projects/2860"> <img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/2860/badge.svg"/> </a>

* Doxygen's Doxygen Documentation: <a href="https://codedocs.xyz/doxygen/doxygen/"><img src="https://codedocs.xyz/doxygen/doxygen.svg"/></a>

* Install: Please read the installation section of the manual (https://www.doxygen.nl/manual/install.html)

* Project stats: https://www.openhub.net/p/doxygen

Issues, bugs, requests, ideas
----------------------------------
Use the [issue](https://github.com/doxygen/doxygen/issues) tracker to report bugs.

Comms
----------------------------------
### Mailing Lists ###

There are three mailing lists:

* doxygen-announce@lists.sourceforge.net     - Announcement of new releases only
* doxygen-users@lists.sourceforge.net        - for doxygen users
* doxygen-develop@lists.sourceforge.net      - for doxygen developers
* To subscribe follow the link to
    * https://sourceforge.net/projects/doxygen/

Source Code
----------------------------------
In May 2013, Doxygen moved from
subversion to git hosted at GitHub
* https://github.com/doxygen/doxygen

Enjoy,

Dimitri van Heesch (doxygen at gmail.com)
