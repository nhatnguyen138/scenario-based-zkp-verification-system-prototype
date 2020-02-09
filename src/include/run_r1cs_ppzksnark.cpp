#ifndef RUN_R1CS_PPZKSNARK_CPP
#define RUN_R1CS_PPZKSNARK_CPP

namespace libsnark {

template<typename ppT>
bool run_r1cs_ppzksnark(const string digest)
{
    typedef libff::Fr<ppT> FieldT;

    // Create the protoboard
    protoboard<FieldT> pb;
    pb.set_input_sizes(1);

    pb_variable_array<FieldT> hash_packed;
    hash_packed.allocate(pb,1,"hash packed");

    digest_variable<FieldT> hash_bits(pb,SHA256_digest_size,"hash_bits");
    digest_variable<FieldT> left_bits(pb,SHA256_digest_size,"left_bits");
    digest_variable<FieldT> right_bits(pb,SHA256_digest_size,"right_bits");

    multipacking_gadget<FieldT> packer(pb,hash_bits.bits,hash_packed,256,"packer");
    packer.generate_r1cs_constraints(true);

    sha256_two_to_one_hash_gadget<FieldT> hasher(pb,left_bits,right_bits,hash_bits,"hash_gadget");
    hasher.generate_r1cs_constraints();

    // Input the hex to the constraint system
    unsigned long list[16];
    string s[16];
    string tmp;
    for (int i=0; i<16; ++i) {
        tmp = digest[i*8+0];
        tmp+= digest[i*8+1];
	tmp+= digest[i*8+2];
	tmp+= digest[i*8+3];
	tmp+= digest[i*8+4];
	tmp+= digest[i*8+5];
	tmp+= digest[i*8+6];
	tmp+= digest[i*8+7];
	s[i]= tmp;
        list[i] = stol(s[i],nullptr,16);
    }

    const libff::bit_vector left_bv = libff::int_list_to_bits({list[0],list[1],list[2],list[3],list[4],list[5],list[6],list[7]},32);
    const libff::bit_vector right_bv = libff::int_list_to_bits({list[8],list[9],list[10],list[11],list[12],list[13],list[14],list[15]},32);

    // Compress the two inputs into one (hash_bits)
    left_bits.generate_r1cs_witness(left_bv);
    right_bits.generate_r1cs_witness(right_bv);
    hasher.generate_r1cs_witness();    
    packer.generate_r1cs_witness_from_bits();

    // Generate R1CS constraint system
    const r1cs_constraint_system<FieldT> cs = pb.get_constraint_system();


    // R1CS ppzkSNARK Generator
    libff::print_header("R1CS ppzkSNARK Generator");
    const r1cs_ppzksnark_keypair<ppT> keypair = r1cs_ppzksnark_generator<ppT>(cs);
    printf("\n"); libff::print_indent(); libff::print_mem("after generator");

    // R1CS ppzkSNARK Prover
    libff::print_header("R1CS ppzkSNARK Prover");
    const r1cs_ppzksnark_proof<ppT> proof = r1cs_ppzksnark_prover<ppT>(keypair.pk, pb.primary_input(), pb.auxiliary_input());
    printf("\n"); libff::print_indent(); libff::print_mem("after prover");

    // R1CS ppzkSNARK Verifier
    libff::print_header("R1CS ppzkSNARK Verifier");
    bool verified = r1cs_ppzksnark_verifier_strong_IC<ppT>(keypair.vk, pb.primary_input(), proof);
    printf("\n"); libff::print_indent(); libff::print_mem("after verifier");


    // Print out primary input the as well as the verification key and proof
    cout << endl << "Primary input : " << hex << pb.primary_input().at(0);
    const r1cs_ppzksnark_verification_key<ppT> vk = keypair.vk;
    print_vk_to_file<ppT>(vk,"../build/vk.dat");
    cout << endl << "Verif. key    : printed to file vk.dat";
    print_proof_to_file<ppT>(proof,"../build/proof.dat");
    cout << endl << "Proof         : printed to file proof.dat" << endl;

    return verified;
}

} //libsnark

#endif
