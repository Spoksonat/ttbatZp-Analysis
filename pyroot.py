import ROOT
from ROOT import TLorentzVector, TH1F

def PT(TLV):
    return TLV.Pt()

# Debemos buscar los muones de mayor p_T que satisfagan la condición de corte. 
# mu_list es una lista ordenada descendentemente según los p_T de los muones.
# Retornamos todos los muones que satisfacen las condiciones. 
# Note que la primera pareja sera la de mayor p_T y delta_R según el cut.
# Queremos dos muones de carga opuesta. Entonces, la multiplicación de sus cargas debe ser menor a 0.
# Cargas en pyroot: https://twiki.cern.ch/twiki/bin/view/CMSPublic/PyRoot
def cuts(mu_list, pt_cut=20, delta_R=0.3):
  global mu_cut
  global cut
  mu_cut = []
  cut = False
  for i, mu_1 in enumerate(mu_list):
    for j, mu_2 in enumerate(mu_list):
      if j > i: 
        if mu_1.Pt() >= pt_cut and mu_2.Pt() >= pt_cut and mu_1.DeltaR(mu_2) > delta_R:
          cut = True
          mu_cut.append((mu_1, mu_2))
  return mu_cut, cut 


# Esto todavía no lo cambio, depende de la señal que me den.
signals = ["DY+jets"]
jobs = [1]

c1 = ROOT.TCanvas("c1", "Titulo")
plot_PT_leptons = TH1F("PT_leptons", "PT_leptons", 100, 0.0, 1000.0)
plot_PT_mu1 = TH1F("PT_mu1", "PT_mu1", 100, 0.0, 1000.0)
plot_PT_mu2 = TH1F("PT_mu2", "PT_mu2", 100, 0.0, 1000.0)
plot_ETA_muons = TH1F("ETA_muons", "ETA_muons", 100, -8.0, 8.0)
plot_PHI_muons = TH1F("PHI_muons", "PHI_muons", 100, -8.0, 8.0)
plot_Delta_R_mu1_mu2 = TH1F("DELTA_R muons", "DELTA_R muons", 100, 0, 10.0)
plot_mRec_mu1_mu2 = TH1F("M_REC muons", "M_REC muons", 100, 0, 100.0)

for n_signal, signal in enumerate(signals):

  f = ROOT.TFile(signal + ".root", "recreate")

  for ind in range(1,jobs[n_signal]+1):
    directory= str("../Sofia/" + signal + "/" + signal + "_" + str(ind) + "/Events/run_01/tag_1_delphes_events.root")
    File = ROOT.TChain("Delphes;1")
    File.Add(directory)
    Number = File.GetEntries()

    print("Signal: " + signal + "_" + str(ind))

    for i in range(Number):
    	#print("Evento: " + str(i))
      Entry = File.GetEntry(i)

      jets = []
      electrons = []
      muons = []
      leptons = []
      METs = []

      EntryFromBranch_j = File.Jet.GetEntries()
      for j in range(EntryFromBranch_j):
        jet = TLorentzVector()
        jet_PT, jet_Eta, jet_Phi, jet_M  = File.GetLeaf("Jet.PT").GetValue(j), File.GetLeaf("Jet.Eta").GetValue(j), File.GetLeaf("Jet.Phi").GetValue(j), File.GetLeaf("Jet.Mass").GetValue(j)
        jet.SetPtEtaPhiM(jet_PT, jet_Eta, jet_Phi, jet_M)
        jets.append(jet)

      EntryFromBranch_e = File.Electron.GetEntries()
      for j in range(EntryFromBranch_e):
        electron = TLorentzVector()
        electron_PT, electron_Eta, electron_Phi, electron_M  = File.GetLeaf("Electron.PT").GetValue(j), File.GetLeaf("Electron.Eta").GetValue(j), File.GetLeaf("Electron.Phi").GetValue(j), 0.000511
        electron.SetPtEtaPhiM(electron_PT, electron_Eta, electron_Phi, electron_M)
        electrons.append(electron)

      EntryFromBranch_mu = File.Muon.GetEntries()
      for j in range(EntryFromBranch_mu):
        muon = TLorentzVector()
        muon_PT, muon_Eta, muon_Phi, muon_M  = File.GetLeaf("Muon.PT").GetValue(j), File.GetLeaf("Muon.Eta").GetValue(j), File.GetLeaf("Muon.Phi").GetValue(j), 0.1056583755
        muon.SetPtEtaPhiM(muon_PT, muon_Eta, muon_Phi, muon_M)
        muons.append(muon)

      EntryFromBranch_MET = File.MissingET.GetEntries()
      for j in range(EntryFromBranch_MET):
        MET = TLorentzVector()
        MET_PT, MET_Eta, MET_Phi, MET_M  = File.GetLeaf("MissingET.MET").GetValue(j), File.GetLeaf("MissingET.Eta").GetValue(j), File.GetLeaf("MissingET.Phi").GetValue(j), 0.0
        MET.SetPtEtaPhiM(MET_PT, MET_Eta, MET_Phi, MET_M)
        METs.append(MET)

      leptons = electrons + muons


      if (len(muons) >= 2):

        jets.sort(reverse = True, key=PT)
        muons.sort(reverse = True, key=PT)
        #j1, j2 = jets[0], jets[1]
        # Estos son los dos muones de mayor pT.
        mu1, mu2 = muons[0], muons[1]
        # Tomamos los muones que satisfagan el corte. Cada uno es un TLorentzVector.
        # Si es estrictamente la pareja de mayor pT, paso muons ordenada. Si no, puede estar desordenada y cogemos la primera
        # pareja que satisfaga la condición
        muons_cut, cut = cuts(muons)
        # Esto me da la pareja de muones de mayor p_T que además cumplen el Delta_R.

        if (cut): 
            leading_pair = muons_cut[0]
            # Cogemos los dos muones que satisfacen el corte
            mu1_cut, mu2_cut = leading_pair[0], leading_pair[1]

        ############################# HISTOS ##########################3

        # Hacemos la gráfica de p_T de los dos muones de mayor p_T
        plot_PT_mu1.Fill(mu1.Pt())
        plot_PT_mu2.Fill(mu2.Pt())
        
        # Sumamos los dos muones cut para hacer la gráfica de masa reconstruida. 
        mu_total = mu1 + mu2
        # Hacemos la gráfica de masa reconstruida de mu_total.
        plot_mRec_mu1_mu2.Fill(mu_total.M())

        for muon in muons:
            plot_ETA_muons.Fill(muon.Eta())
            plot_PHI_muons.Fill(muon.Phi())

        #MET
        #for MET in METs:
            #plot_MET.Fill(MET.Pt())

        if (cut):
            # Hacemos la grafica de Delta_R de los dos muones con mayor pT y Delta_R > 0.3
            plot_Delta_R_mu1_mu2.Fill(mu1_cut.DeltaR(mu2_cut))




  plot_PT_leptons.Draw("HIST")
  plot_ETA_muons.Draw("HIST")
  plot_PHI_muons.Draw("HIST")
  plot_PT_mu1.Draw("HIST")
  plot_PT_mu2.Draw("HIST")
  plot_Delta_R_mu1_mu2.Draw("HIST")
  plot_mRec_mu1_mu2.Draw("HIST")

  plot_PT_leptons.Write()
  plot_ETA_muons.Write()
  plot_PHI_muons.Write()
  plot_PT_mu1.Write()
  plot_PT_mu2.Write()
  plot_Delta_R_mu1_mu2.Write()
  plot_mRec_mu1_mu2.Write()

  f.Close()

  plot_PT_leptons.Reset("ICESM")
  plot_ETA_muons.Reset("ICESM")
  plot_PHI_muons.Reset("ICESM")
  plot_PT_mu1.Reset("ICESM")
  plot_PT_mu2.Reset("ICESM")
  plot_Delta_R_mu1_mu2.Reset("ICESM")
  plot_mRec_mu1_mu2.Reset("ICESM")
  
