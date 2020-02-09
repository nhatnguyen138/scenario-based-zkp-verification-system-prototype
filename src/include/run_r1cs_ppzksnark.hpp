#ifndef RUN_R1CS_PPZKSNARK_HPP
#define RUN_R1CS_PPZKSNARK_HPP

#include <libff/common/utils.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libsnark/gadgetlib1/pb_variable.hpp>
#include <libsnark/gadgetlib1/gadgets/hashes/sha256/sha256_gadget.hpp>

#include <libff/common/default_types/ec_pp.hpp>
#include <libsnark/common/default_types/r1cs_ppzksnark_pp.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp>

#include "util.hpp"	// print out vk and proof data

using namespace std;

namespace libsnark {

template<typename ppT>
bool run_r1cs_ppzksnark(const string digest);

} //libsnark

#include "run_r1cs_ppzksnark.cpp"

#endif
