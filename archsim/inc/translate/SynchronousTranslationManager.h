/*
 * File:   SynchronousTranslationManager.h
 * Author: s0457958
 *
 * Created on 06 August 2014, 09:21
 */

#ifndef SYNCHRONOUSTRANSLATIONMANAGER_H
#define	SYNCHRONOUSTRANSLATIONMANAGER_H

#include "translate/TranslationManager.h"
#include "translate/llvm/LLVMOptimiser.h"
#include "util/PagePool.h"

namespace gensim
{
	class Processor;
}

namespace llvm
{
	class LLVMContext;
}

namespace archsim
{
	namespace translate
	{
		namespace profile
		{
			class Region;
		}

		class TranslationEngine;
		class SynchronousTranslationManager : public TranslationManager
		{
		public:
			SynchronousTranslationManager(util::PubSubContext *psctx);
			~SynchronousTranslationManager();

			bool Initialise() override;
			void Destroy() override;

			bool TranslateRegion(gensim::Processor& cpu, profile::Region& rgn, uint32_t weight);

		private:
			TranslationTimers timers;
			::llvm::LLVMContext *llvm_ctx;
			llvm::LLVMOptimiser optimiser;

			util::PagePool code_pool;
		};

	}
}

#endif	/* SYNCHRONOUSTRANSLATIONMANAGER_H */

