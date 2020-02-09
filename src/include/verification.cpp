string digest_formatting(string& result)
{
    // Convert message to hex format
    ostringstream ret;
    unsigned long c;
    for (string::size_type i=0; i<result.length(); ++i)
    {
        c = (unsigned long)(unsigned char)result[i];
        ret << hex << nouppercase << c;
    }
    result = ret.str();

    // Make sure the hex digest has the fixed size of 128
    if (result.length()>128)
    	result=result.substr(0,128);
    else if (result.length()<128)
        for (int i=result.length(); i<128; ++i)
            result+='0';
    
    return result;
}


bool age_verification(int number)
{
    char Filename[] = "../dat.txt";			// digital certificate
    default_r1cs_ppzksnark_pp::init_public_params();
    libff::start_profiling();

    string digest;
    ifstream f(Filename);
    if (f)
    {
        libff::enter_block("Fetch data");
        string a,b;
        string date,month,year;
        int count=0;
        bool read = true;
        while (read)
        {
            f >> a >> b;
            if (a=="year")
            {
                year = b;
                ++count;
            }
            else if (a=="month")
            {
                month = b;
                ++count;
            }
            else if (a=="date")
            {
                date = b;
                ++count;
            }
            if (count==3)
                read = false;
        }
        digest = year+"-"+month+"-"+date;

        // Fetch current date to calculate the current age
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string cyear  = to_string(1900 + ltm->tm_year);
        string cmonth = to_string(1 + ltm->tm_mon);
        string cdate  = to_string(ltm->tm_mday);

        int age = stoi(cyear) - stoi(year);
        if (stoi(cmonth)-stoi(month)<0)
            --age;
        else if (stoi(cmonth)-stoi(month)==0)
            if (stoi(cdate)-stoi(date)<0)
                --age;
        libff::leave_block("Fetch data");

        // Check if this is your actual date of birth
        libff::print_header("Age Verification");
        digest = digest_formatting(digest);
        printf("\n"); libff::enter_block("Call to run_r1cs_ppzksnark");
        const bool run = run_r1cs_ppzksnark<default_r1cs_ppzksnark_pp>(digest);
        printf("\n"); libff::leave_block("Call to run_r1cs_ppzksnark");

        // Check if you are old enough
        libff::enter_block("Calculate age");
        string seed = "cba1977v";
        string proof = sha256(seed);
        string encrypted_age = sha256(seed);

        for (int i=1; i<=age-number+1; ++i)
            proof = sha256(proof);
        for (int i=1; i<=age+1; ++i)
            encrypted_age = sha256(encrypted_age);

        string verified = proof;
        for (int i=1; i<=number; ++i)
            verified = sha256(verified);

        const bool run2 = (verified==encrypted_age);
        libff::leave_block("Calculate age");

        // return true if both conditions are met
        return (run && run2);
    }
    else
    {
        cerr << "File not found.\n\n";
        exit(1);
    }
    return false;
}


bool address_verification()
{
    char Filename[] = "../dat.txt";			// digital certificate
    default_r1cs_ppzksnark_pp::init_public_params();
    libff::start_profiling();

    string digest;
    ifstream f(Filename);
    if (f)
    {
        libff::enter_block("Fetch data");
        string a,b;
        string pcode,state,city,street,number,unit;
        int count = 0;
        bool read = true;
        while (read)
        {
            f >> a >> b;
            if (a=="pcode")
            {
                pcode = b;
                ++count;
            }
            else if (a=="state")
            {
                state = b;
                ++count;
            }
            else if (a=="city")
            {
                city = b;
                ++count;
            }
            else if (a=="street")
            {
                street = b;
                ++count;
            }
            else if (a=="number")
            {
                number = b;
                ++count;
            }
            else if (a=="unit")
            {
                unit = b;
                ++count;
            }
            if (count==6)
                read = false;
            }
            if (unit=="N/A")
                digest=number+" "+street+" street, "+city+" "+state+", "+pcode;
            else
                digest="Unit "+unit+", "+number+" "+street+" street, "+city+" "+state+", "+pcode;
        libff::leave_block("Fetch data");

        libff::print_header("Address Verification");
        digest = digest_formatting(digest);
        printf("\n"); libff::enter_block("Call to run_r1cs_ppzksnark");
        const bool run = run_r1cs_ppzksnark<default_r1cs_ppzksnark_pp>(digest);
        printf("\n"); libff::leave_block("Call to run_r1cs_ppzksnark");
        return run;
    }
    else
    {
        cerr << "File not found.\n\n";
        exit(1);
    }
    return false;
}



// Phone number verification process
bool phone_number_verification()
{
    char Filename[] = "../dat.txt";			// digital certificate
    default_r1cs_ppzksnark_pp::init_public_params();
    libff::start_profiling();

    string digest;
    ifstream f(Filename);
    if (f)
    {
        libff::enter_block("Fetch data");
        string a,b;
        string fname,lname,phone;
        int count=0;
        bool read = true;
        while (read)
        {
            f >> a >> b;
            if (a=="fname")
            {
                fname = b;
                ++count;
            }
            else if (a=="lname")
            {
                lname = b;
                ++count;
            }
            else if (a=="phone")
            {
                phone = b;
                ++count;
            }
            if (count==3)
                read = false;
        }
        digest = fname+" "+lname+" "+phone;
        libff::leave_block("Fetch data");

        libff::print_header("Phone Number Verification");
        digest = digest_formatting(digest);
        printf("\n"); libff::enter_block("Call to run_r1cs_ppzksnark");
        const bool run = run_r1cs_ppzksnark<default_r1cs_ppzksnark_pp>(digest);
        printf("\n"); libff::leave_block("Call to run_r1cs_ppzksnark");
        return run;
    }
    else
    {
        cerr << "File not found.\n\n";
        exit(1);
    }
    return false;
}
   
