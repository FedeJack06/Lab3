
// E' un banalissimo fit lineare
// **********************************************************

void attOtt(){

    ifstream file("conc.dat");
    double conc,angolo;
    auto gr = new TGraphErrors();
    double e = 2*TMath::Pi()/100;

    int i = 0;
    while (file >> conc >> angolo)
    {
        gr->SetPoint(i, conc, angolo);
        gr->SetPointError(i, 0.01*conc, 0.02);
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