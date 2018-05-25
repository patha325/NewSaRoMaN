// Read data (CERN staff) from an ascii file and create a root file with a Tree.
// see also a variant in staff.C
// Author: Rene Brun
   
TFile *rootTest(Int_t get=0, Int_t print=1) {

   Int_t           Category;

   //FILE *fp = fopen("example.txt","r");

   TFile *hfile = 0;

   hfile = TFile::Open("example2.root","RECREATE");
   TTree *tree = new TTree("T","Reconstruction data");

   //tree->ReadFile("example2.txt","mompull:Charge:mom:cov");

   tree->ReadFile("example2.txt","Event:MCtr_Mom:Charge:mom:cov:track_len");

   //tree->Print();
   tree->Write();


   /*
   tree->Branch("Category",&Category,"Category/I");
   char line[80];
   while (fgets(&line,80,fp)) {
     sscanf(&line[0],"%d",&Category);
      tree->Fill();
   }
   if (print) tree->Print();
   tree->Write();

   fclose(fp);
   */   
   delete hfile;
   return 0;
}
