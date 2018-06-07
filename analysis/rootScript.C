{
  //TFile *_file0 = TFile::Open("B4.root");

  TChain* T = new TChain("tree");
  T->Add("../recOut.root");
  
  //T->Draw("MCtr_Mom:track_len","","COLZ");
  TH2D* momentum = new TH2D("momentum",";True Momentum (GeV/c);Rec Momentum (GeV/c)",100,0,4000,100,0,4000);

  TH2D* momentumDiff = new TH2D("momentumDiff",";True Momentum (GeV/c);Rec-True Momentum (GeV/c)",100,0,4000,100,-5000,5000);

  TH1D* eff = new TH1D("eff",";True Momentum (GeV/c); Fractional Efficiency",20, 0, 4000);
    TH1D* all = new TH1D("all",";True Momentum (GeV/c); Fractional Efficiency",20, 0, 4000);

    //T->Draw("abs(mom)-abs(MCtr_Mom):abs(MCtr_Mom)")
    //diff on y, mom on x;
    
  T->Draw("abs(Rec_mom):abs(MCtr_Mom)>>momentum","","COLZ");

  T->Draw("abs(Rec_mom)-abs(MCtr_Mom):abs(MCtr_Mom)>>momentumDiff","","COLZ");

  T->Draw("abs(MCtr_Mom)>>eff","Rec_Charge==-1","COLZ");
  T->Draw("abs(MCtr_Mom)>>all","","COLZ");
  eff->Sumw2();
  all->Sumw2();
  eff->Divide(all);
  eff->Draw();

}
