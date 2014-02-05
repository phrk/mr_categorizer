/* 
 * File:   WordOccurs.cpp
 * Author: phrk
 * 
 * Created on February 5, 2014, 10:54 AM
 */

#include "WordOccurs.h"

void WordOccurs::restore(const std::string &_dump)
{
	Categorizer::WordOccurs occurs_pb;
	occurs_pb.ParseFromString(_dump);
	for (int i = 0; i < occurs_pb.category_occurs_size(); i++) {
		Categorizer::WordOccurs_CategoryOccurs category_occurs_pb = 
				occurs_pb.category_occurs(i);
		m_occurs.insert(std::pair<uint64_t, uint64_t>( category_occurs_pb.category(),
								category_occurs_pb.noccurs() ) );
	}
}

void WordOccurs::dump(std::string &_dump) const
{
	Categorizer::WordOccurs occurs_pb;

	std::tr1::unordered_map<uint64_t, uint64_t>::const_iterator it = 
			m_occurs.begin();
	std::tr1::unordered_map<uint64_t, uint64_t>::const_iterator end = 
			m_occurs.end();
	
	while (it != end) {
		Categorizer::WordOccurs::CategoryOccurs *category_occurs = 
					occurs_pb.add_category_occurs();
		category_occurs->set_category(it->first);
		category_occurs->set_noccurs(it->second);
		it++;
	}
	_dump = occurs_pb.SerializeAsString();
}

WordOccurs::~WordOccurs()
{
	m_occurs.clear();
}
