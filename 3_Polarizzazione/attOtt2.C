void attOtt2(){

    ifstream file("conc2.dat");
    double conc,angolo,e;
    auto gr = new TGraphErrors();


    int i = 0;
    while (file >> conc >> angolo >> e)
    {
        gr->SetPoint(i, conc, angolo);
        gr->SetPointError(i, 0.01*conc, e);
        i++;
    }

    auto f = new TF1("f","[0]+[1]*(x)",-0.1,0.6);
    auto c = new TCanvas("c","c");
    f->SetParameters(0,1);
    c->Draw();
    c->DrawFrame(-0.1,-0.15,0.6,0.5);
    gStyle->SetOptFit(1011);
    gr->SetMarkerStyle(20);
    gr->Draw("P");
    gr->SetTitle("Concentrazione di glucosio vs angolo di rotazione polarizzazione");
    gr->GetXaxis()->SetTitle("angolo [rad]");
    gr->GetYaxis()->SetTitle("Concentrazione relativa []");

    gr->Fit("f","R");
    gr->Print();
};