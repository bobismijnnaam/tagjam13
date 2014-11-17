#ifndef NNB_LOG_HPP
#define NNB_LOG_HPP

// Public
#include <iostream>

// Private
#include "../utils/macros.hpp"
#include "../utils/NewlineOnDestruct.hpp"

#define NNB_LOG (nnb::NewlineOnDestruct(), std::cout << "[" << __BASE_FILE__ << ":" << NNB__LINE__S << "] ")

// TODO: Does this even work?
#ifdef DEBUG
	#define NNB_DEBUG_LOG NNB_LOG
#else
	#define NNB_DEBUG_LOG //
#endif

#endif