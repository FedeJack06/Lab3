void optAct(){

    ifstream file("dati.dat");
    double conc,angolo;
    auto gr = new TGraphErrors();

    int i = 0;
    while (file >> conc >> angolo)
    {
        gr->SetPoint(i, angolo, conc);
        gr->SetPointError(i, 0, 0);
        i++;
    }

    auto f = new TF1("f","[0]+[1]*(x-[2])",0.,0.);
    f->SetParameters(0,1,0);

    gStyle->SetOptFit(1011);
    gr->SetMarkerStyle(20);
    gr->Draw("AP");
    gr->SetTitle("Concentrazione di glucosio vs angolo di rotazione polarizzazione");
    gr->GetXaxis()->SetTitle("angolo [rad]");
    gr->GetYaxis()->SetTitle("Concentrazione relativa []");

    gr->Fit("f");
};