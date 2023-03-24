
void linearizzazione(){

    ifstream file("tot_4.lvm");

    auto gr1 = new TGraphErrors(); //grafico dei dati
    auto gr2 = new TGraphErrors(); //grafico linearizzato

    int i = 0;
    double e_VSbarra = 0.0035/(2*sqrt(3));
    double TSbarra,TRes,t; //ingressi
    double VSbarra,VRes;
    double VRes_max = 0;
    double VRes_min = 0;
    double dVRes = 0;
    double VImpulso,R_pt100;
    double I = 0.001;
    double temp_max = 10; //massimo della temperatura
    double t_max = 0; //tempo corrispondende al massimo della temperatura
    double d = 0.021; //distanza della misuraione della temperatura dall estremo a cui diamo l impulso
    double cost_conversione = 41e-6;
    bool control_time = true;
    double t1;
    double guadagno = 2060;
    while (file >> VImpulso >> t >> VRes >> VSbarra)
    {
        //MANCA IL CALCOLO DELLE DIFFERENZA DELLA TENSIONE VRES PER IL CALCOLO DELLA RESISTENZA DELLA PT100 
        
        TSbarra = VSbarra/(guadagno*cost_conversione);
        R_pt100 = dVRes/I;
        TRes = 14e-04*pow(R_pt100,2) + 2.2959 * R_pt100 + 29.77;
        if (TSbarra <= temp_max) //cerco il massimo della temperatura
        {
            temp_max = TSbarra;
            t_max = t;
        }

        gr1->SetPoint(i,t,TSbarra);
        double k = log(TSbarra*sqrt(t));
        if((t >= 14) && (k < 10) && (k > 0) && (1/t > 0.005))
        //if((t >= 14))
        {
            gr2->SetPoint(gr2->GetN(), 1./t, k);
        }
        i++;
    }
    
    double ord_D = (d*d)/(2*t_max);
    //cout << t_max << endl;
    cout << "il valore di D usando il valore massimo di temperatura ad x fissato è: " << ord_D << endl;

    auto c1 = new TCanvas();
    auto c2 = new TCanvas();

    gr1->SetMarkerStyle(20);
    gr2->SetMarkerStyle(20);

    c1->cd();
    gr1->Draw("AP");

    c2->cd();
    gr2->Draw("AP");

    auto f2 = new TF1("f2","log([0]/sqrt([1]))+x*(([2]*[2])/(4*[1]))",0.033,0.073); //fit lineare
    auto f1 = new TF1("f1","-1*[0]/(sqrt([1])*sqrt(x))*exp(-([3]*[3])/(4*[1]*x))+[2]",13.7,30);

    f1->SetParameters(0.4, 9.9e-6, 4, d);
    f1->FixParameter(3, d);
    f2->SetParameters(0.4, ord_D, d); //[0] Costante, [1] D, [2] distanza

    // f1->SetParLimits(1,1e-03,1e-08);
    // f1->SetParLimits(3,0.018,0.024);
    f1->SetParLimits(2,0,10);
    f1->SetParLimits(0,-1,3);
//FIT T(t)
    gr1->Fit("f1","R");
    double p1 = f1->GetProb();
    cout << "il p-value per il fit è: " << p1 << endl;
    double D1 = f1->GetParameter(1);
    cout << "il valore di D ottenuto con il metodo di fit della temperatura in funzione del tempo è: " << D1 << endl;

//FIT LINEARIZZAZIONE
    gr2->Fit("f2","R");
    double p2 = f2->GetProb();
    cout << "il p-value per la linearizzazione è: " << p2 << endl;
    double D2 = f2->GetParameter(1);
    cout << "il valore di D ottenuto con il metodo di linearizzazione: " << D2 << endl;

    // gr2->RemovePoint(0);
    //gr2->Print();
};