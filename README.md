**Steps to create datacards and Limit Calculation**

**Step 1 :  Getting ready with signal and bkgs with signal region binning :**
  * I use very basic and clear method to do this step which is as follows.
  * As I have different/variable bin size in my final distribution, I create a .txt file using **bkg_yield.C** for that particular binning. The binning can be changed/optimized using bins[n] array in the script.
  * The input to **bkg_yield.C** is list of bkgs as shown in **bkg_list.txt** and creates output yield file for different bkgs. Similar is the scenario for signal samples
  
**Step 2 :  Creating datacards :** 
  * To create datacards : **create_datacard.py**
  * This script is for mutau channel (2018). In this channel, we have 1 signal and 5 backgrounds and one bin-dependent systematic uncertainty
  * The input to this script is step 1 output txt files and mass of signal sample as follows (for VBF Z'):
    * python create_datacard.py 250 signal.txt bkg1.txt bkg2.txt bkg3.txt bkg4.txt bkg5.txt sys.txt
  * This creates datacards for each bin with name : VBF_card_M250_bin**.txt where ** : 1,2,3,...12 (VBF Z')
 
**Step 3:  Setting up Higgs Combine Tool :**
  * Higgs Combine tool can be run on lxplus or lpc. To setup the combine tool, linked manual ([Here](http://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/#setting-up-the-environment-and-installation))  has been followed and list of instructions are as below:
    * export SCRAM_ARCH=slc7_amd64_gcc700
    * cmsrel CMSSW_10_2_13
    * cd CMSSW_10_2_13/src
    * cmsenv
    * git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
    * cd HiggsAnalysis/CombinedLimit
    * scramv1 b
**Step 4: Combining datacards and running Combine Tool :**
    * cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit/scripts
    * rm *root
    * rm *.txt
    * Copy your datacards in this directory
    * python combineCards.py VBF_card_M250_bin**.txt > VBF_card_M250.txt
    * To Calculate the asymptotic limit :
      * combine -M Asymptotic VBF_card_M250.txt
    * to get the significance calculation
      * combine -M ProfileLikelihood --signif VBF_card_M250.txt
