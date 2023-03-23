
void linearizzazione(){

    ifstream file("TOT_4.lvm");

    auto gr1 = new TGraphErrors(); //grafico dei dati
    auto gr2 = new TGraphErrors(); //grafico linearizzato

    int i = 0;
    double TSbarra,TRes,t; //ingressi
    double VSbarra,VRes;
    double VRes_max = 0;
    double VRes_min = 0;
    double dVRes = 0;
    double VImpulso,R_pt100;
    double I = 0.001;
    double temp_max = 0; //massimo della temperatura
    double t_max = 0; //tempo corrispondende al massimo della temperatura
    double d = 0.021; //distanza della misuraione della temperatura dall estremo a cui diamo l impulso
    double cost_conversione = 41e-6;
    bool control_time = true;
    double t1;
    double guadagno = 2000;
    while (file >> VImpulso >> t >> VRes >> VSbarra)
    {
        
        //MANCA IL CALCOLO DELLE DIFFERENZA DELLA TENSIONE VRES PER IL CALCOLO DELLA RESISTENZA DELLA PT100        
        if (control_time)
        {
            t1 = t;
            control_time = false;
        }
        if ((t-t1) > 0.2)
        {
            if (VRes >= VRes_max)
            {
                VRes_max = VRes;
            }
            else if(VRes <= VRes_min)
            {
                VRes_min = VRes;
            }
            dVRes = abs(VRes_max-VRes_min);
            control_time = true;
        }
        
        
        TSbarra = VSbarra/(guadagno*cost_conversione);
        R_pt100 = dVRes/I;
        TRes = 14e-04*pow(R_pt100,2) + 2.2959 * R_pt100 + 29.77;
        if (TSbarra > temp_max) //cerco il massimo della temperatura
        {
            temp_max = TSbarra;
            t_max = t;
        }

        gr1->SetPoint(i,t,TSbarra);
        if(t >= 0.001)
        {
            gr2->SetPoint(i, 1./t, log(abs(TSbarra-TRes)*sqrt(t)));
        }
        i++;
    }
    
    double ord_D = (d*d)/(2*t_max);
    cout << "il valore di D usando il valore massimo di temperatura ad x fissato è: " << ord_D << endl;

    auto c1 = new TCanvas();
    auto c2 = new TCanvas();

    gr1->SetMarkerStyle(20);
    gr2->SetMarkerStyle(20);

    c1->cd();
    gr1->Draw("AP");

    c2->cd();
    gr2->Draw("AP");

    auto f2 = new TF1("f2","log([0]/sqrt([1]))+x*(([2]*[2])/(4*[1]))",0.035,0.077); //fit lineare
    auto f1 = new TF1("f1","-1*[0]*sqrt(x)/(sqrt([1]))*exp(-([3]*[3])*x/(4*[1]))+[2]",13,30);

    f1->SetParameters(40, ord_D, TRes, d);
    f2->SetParameters(40, ord_D, d); //[0] = conducubilita

    f2->SetParLimits(0,26,65);
//FIT T(t)
    gr1->Fit("f1");
    double p1 = f1->GetProb();
    cout << "il p-value per il fit è: " << p1 << endl;
    double D1 = f1->GetParameter(1);
    cout << "il valore di D ottenuto con il metodo di fit della temperatura in funzione del tempo è: " << D1 << endl;

//FIT LINEARIZZAZIONE
    gr2->Fit("f2");
    double p2 = f2->GetProb();
    cout << "il p-value per la linearizzazione è: " << p2 << endl;
    double coeff_ang = f2->GetParameter(0);
    double D2 = -(d*d)/(4*coeff_ang);
    cout << "il valore di D ottenuto con il metodo di linearizzazione: " << D2 << endl;

    gr2->RemovePoint(0);
    gr2->Print();
};