/* 
 * File:   main_mr_categorizer.cpp
 * Author: phrk
 *
 * Created on February 4, 2014, 6:41 PM
 */

#include <cstdlib>

#include "CategorizerMR.h"
#include "CategorizerBatch.h"

#include "../hspliter/hSpliterLocal.h"

#include "../tetramorph/mapreduce/core/MRNodeDispatcher.h"

#include "../lang/DictManager.h"

using namespace std;

/*
 * 
 */

htQuerierPtr word_querier;
htConnPoolPtr conn_pool;

void onFinished(MRInterResultPtr result)
{
	
	DictPtr en_dict (new Dict(conn_pool, "highinit_q", "en_words", "en_stems",
				LangDetect::EN) );
	DictPtr ru_dict (new Dict (conn_pool, "highinit_q", "ru_words", "ru_stems",
				LangDetect::RU) );
	
	std::vector<DictPtr> dicts;
	dicts.push_back(en_dict);
	dicts.push_back(ru_dict);
	
	DictManager dict_man(dicts);
	
	result->waitFlushFinished();
	result->waitInitReading();
	
	std::ofstream result_filename_file("result_filename");
	result_filename_file << result->getFileName() << std::endl;
	result_filename_file.close();
	
	std::cout << "Result file: " << result->getFileName() << std::endl;
	std::cout << "Finished. Keys: " << result->size() << std::endl;
	
	std::ofstream out_debug("out_debug");
	
	Int64VecPtr keys = result->getKeys();
	for (int i = 0; i<1000; i++) {
		result->preload(keys->at(i), 1);
		
		out_debug << "key: " << dict_man.getWord( keys->at(i) ) << ": ";
		std::cout << "key: " << dict_man.getWord( keys->at(i) ) << ": ";
		WordOccurs *occurs = (WordOccurs*) result->getEmit(keys->at(i), 1);
		std::tr1::unordered_map<uint64_t, uint64_t>::iterator it = 
				occurs->m_occurs.begin();
		while (it != occurs->m_occurs.end()) {
			out_debug << it->first << "(" << it->second << ") ";
			std::cout << it->first << "(" << it->second << ") ";
			it++;
		}
		out_debug << std::endl;
		std::cout << std::endl;
	}
	out_debug.close();
}

void onProgress(MRProgressBar bar)
{
	std::cout << "MAP: " << bar.map_p << " REDUCE: " << bar.red_p << std::endl;
}

int main(int argc, char** argv) {

	std::string ns = "highinit_q";
	std::string job_name = "mr_categorizer";
	
	conn_pool.reset(new htConnPool("localhost", 38080, 1) );
	
	//word_querier.reset(new htQuerier(conn_pool, ns, "ru_words"));
	/*
	htKeyScannerPtr key_scanner( new htKeyScanner(conn_pool, ns, "pages") );	
	while (!key_scanner->end()) {
		std::cout << key_scanner->getNextKey() << std::endl;
	}
	return 0;
	*/
			
	hThreadPool* th_pool = new hThreadPool(4);
	th_pool->run();
	
	hSpliterLocalPtr spliter (new hSpliterLocal(conn_pool,
											ns,
											"pages", 
											job_name,
											hSpliterClient::START,
										1000) );

	CategorizerMR* MR = new CategorizerMR();
	
	MRNodeDispatcherPtr mr_node(new MRNodeDispatcher(th_pool, MR, "/Volumes/seagate/", 
											boost::bind(&onFinished, _1) ) );
	
	mr_node->setProgressBar(boost::bind(&onProgress, _1));
	
	size_t nbatches = 0;
	KeyRange range = spliter->getSplit();
	std::cout << "got range " << range.toString() << std::endl;
	while (range.ok()) {
		htCollScannerPtr scanner (new htCollScanner(conn_pool,
												ns,
												"pages",
												"text_parsed",
												range) );
		CategorizerBatch *batch = new CategorizerBatch(scanner);
		mr_node->addBatch(batch);
		range = spliter->getSplit();
		std::cout << "got range " << range.toString() << std::endl;
		nbatches++;
		//break;
	}
	
	std::cout << "Set " << nbatches << " batches\n";
	mr_node->noMoreBatches();
	th_pool->join();
	
	return 0;
}

