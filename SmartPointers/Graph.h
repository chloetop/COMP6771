 /////////////////////////////////////////////////////////////// 
 //    														  //
 //                         ###    ######   ######      ##    //
 //                        ##      ##  ##   ##  ##     ###    //
 //      #####    #####   ##           ##       ##      ##    //
 //     ##       ##       #####       ##       ##       ##    //
 //     ##        ####    ##  ##      ##       ##       ##    //
 //     ##           ##   ##  ##     ##       ##        ##    //
 //      #####   #####     ####      ##       ##        ##    //
 //    														  //
 //     		COMP6771 Assignment_3: SmartPointers		  //
 //     					HEADER FILE					  	  //
 //    														  //
 ///////////////////////////////////////////////////////////////


#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <iostream>
#include <exception>
#include <map>
#include <set>
#include <typeinfo>

namespace gdwg
{	

	template <typename N, typename E> class Graph;
	template <typename N, typename E> class Node_Iterator
	{
		public:
			typedef typename Graph<N,E>::Node Node;

			typedef std::ptrdiff_t                     difference_type;
			typedef std::forward_iterator_tag          iterator_category;
			const typedef N                            value_type;
			const typedef N*                           pointer;
			const typedef N&                           reference;

			// value type
			reference operator*() const {
				
				return (*it)->val_;
			}

			// reference type
			pointer operator->() const {
				return &(operator*());
			}

			// pre increment
			Node_Iterator& operator++() {
				++it;
				if (it==mynodes_.end()) end = true;
				return *this;
			}

			// post increment
			Node_Iterator operator++(int) {
				Node_Iterator tmp = *this;
				++it;
				if (it==mynodes_.end()) end = true;
				return tmp;
			}

			// equals
			bool operator==(const Node_Iterator& other) const {
				
				if (end && other.end) {
					return true;
				} else if (end || other.end) {
					return false;
				}
				return !(operator*() < (*other.it)->val_) && !((*other.it)->val_ < operator*());
			};

			// not equals
			bool operator!=(const Node_Iterator& other) const {
				
				return !operator==(other);
			}

			// Assignment
			Node_Iterator& operator=(const Node_Iterator &ni) {
				mynodes_ 	= ni.mynodes_;
				end 		= ni.end;
				it 			= std::find(mynodes_.begin(),mynodes_.end(),*ni.it);
				
				return *this;
			}

			//const
			Node_Iterator(const std::map<N,std::shared_ptr<Node>> *nodes = nullptr)
			{
				// if it is an end iterator or the graph is empty
				// create a one after the end iterator
				if (nodes == nullptr || (*nodes).empty()) {
					end = true;
				// otherwise add all the elements of nodes_ to the iterator container
				} else {
					std::for_each((*nodes).begin(),(*nodes).end(),
						[this] (const std::pair<N,std::shared_ptr<Node>>& p) 
							{
								p.second->update();
								mynodes_.push_back(p.second);
							});
				// sort the iterator container nodes
					std::sort(mynodes_.begin(),mynodes_.end(),
						[] (const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
							return a->numEdges_ != b->numEdges_ ? a->numEdges_ < b->numEdges_ : a->val_ < b->val_;
							});
					it = mynodes_.begin();
					end = false;
				}
			}

			// constructor without internal sort feature ... Not the best way to implement this ... but works.
			Node_Iterator(bool a, const std::map<N,std::shared_ptr<Node>> *nodes = nullptr)
			{
				// if it is an end iterator or the graph is empty
				// create a one after the end iterator
				if (nodes == nullptr || (*nodes).empty()) {
					end = true;
				// otherwise add all the elements of nodes_ to the iterator container
				} else {
					std::for_each((*nodes).begin(),(*nodes).end(),
						[this] (const std::pair<N,std::shared_ptr<Node>>& p) 
							{
								p.second->update();
								mynodes_.push_back(p.second);
							});
					it = mynodes_.begin();
					end = false;
				}
			}

		private:
			bool end;
			typename std::vector<std::shared_ptr<Node>>::iterator it;
			typename std::vector<std::shared_ptr<Node>> mynodes_;

	};

	template <typename N, typename E> class Edge_Iterator
	{
		public:
			friend class Graph<N,E>;

			typedef typename Graph<N,E>::Node Node;
			typedef typename Graph<N,E>::Edge Edge;

			typedef std::ptrdiff_t                     difference_type;
			typedef std::forward_iterator_tag          iterator_category;
			const typedef std::pair<N,E>               value_type;
			const typedef value_type*                  pointer;
			const typedef value_type&                  reference;

			// value type
			reference operator*() const {
				if (auto tmp = (*it)->dest.lock()) {
					auto tmp2 = new std::pair<N,E>(tmp->val_,(*it)->val_);
					return *tmp2; 
				}
				throw std::runtime_error("getDest: Node Does not exist");				
			}

			// reference type
			pointer operator->() const {
				return &(operator*());
			}

			// pre increment
			Edge_Iterator& operator++() {
				++it;
				if (it==myedges_.end()) end = true;
				return *this;
			}

			// post increment
			Edge_Iterator operator++(int) {
				Edge_Iterator tmp = *this;
				++it;
				if (it==myedges_.end()) end = true;
				return tmp;
			}

			// equals
			bool operator==(const Edge_Iterator& other) const {
				
				if (end && other.end) {
					return true;
				} else if (end || other.end) {
					return false;
				}
				return !(operator*().second < (*other.it)->val_) && !((*other.it)->val_ < operator*().second);
			};

			// not equals
			bool operator!=(const Edge_Iterator& other) const {
				
				return !operator==(other);
			}

			//Edge_Iterator(std::vector<std::shared_ptr<Edge>> v)
			Edge_Iterator(const std::shared_ptr<Node> node = nullptr)
			{
				if (node == nullptr || node->edges_.empty()) {
					end = true;
				} else {
					(*node).update();
					// create a vector of all the edges
					std::for_each(node->edges_.begin(),node->edges_.end(),
						[this] (const std::shared_ptr<Edge>& e)
							// only add them if the still exist
							{ if (auto tmpa = e->dest.lock()) {
								myedges_.push_back(e); }
							});				
					if (myedges_.empty()) {
						
						end = true;
						
					} else {
						std::sort(myedges_.begin(),myedges_.end(),
							[] (const std::shared_ptr<Edge>& a, const std::shared_ptr<Edge>& b) {
								if (!(a->val_ < b->val_) && !(b->val_ < a->val_)) {
									if (auto tmpa = a->dest.lock()) {
										if (auto tmpb = b->dest.lock()) {
											return tmpa->val_ < tmpb->val_;
										}
									}
								}
								return a->val_ < b->val_;
							});
						it = myedges_.begin();
						end = false;
					}
				}
			}


		private:
			N getDest () {
				if (auto tmp = (*it)->dest.lock()) {
					return tmp->val_;
				}
				throw std::runtime_error("getDest: Node Does not exist");
			}


			bool end;
			typename std::vector<std::shared_ptr<Edge>>::iterator it;
			typename std::vector<std::shared_ptr<Edge>> myedges_;
	};


	#include "Graph.tem"
}

#endif
