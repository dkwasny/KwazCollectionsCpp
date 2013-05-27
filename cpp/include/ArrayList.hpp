#ifndef _KWAZ_ARRAY_LIST_
#define _KWAZ_ARRAY_LIST_

// Default configuration values
#define ARRAY_LIST_INITIAL_CAPACITY 10

/* The multiplier used to expand an ArrayList's backing array whenever the
 * list's size equals its capacity.
 *
 * EX: A multiplier of 2 doubles the capacity.
 */
#define ARRAY_LIST_ADD_REALLOCATION_MULTIPLIER 2

/* The threshold value is multiplied by an ArrayList's size.
 * If the resulting value is <= the ArrayList's capacity,
 * a reallocation (shrink) of the backing array is performed.
 *
 * EX: A threshold of 4 requires <= 25% of an ArrayList's capacity
 * to be used before triggering a reallocation during removal.
 */
#define ARRAY_LIST_REMOVE_REALLOCATION_THRESHOLD 4

/* The divisor used to shrink an ArrayList's backing array whenever the
 * list's size * reallocation threshold is greater than the list's capacity.
 *
 * EX: A divisor of 2 halfs the capacity.
 */
#define ARRAY_LIST_REMOVE_REALLOCATION_DIVISOR 2

#include "IList.hpp"
#include <cstring>

class ArrayList : public IList {
	public:
		ArrayList();
		ArrayList(
			const size_t pCapacity,
        		const unsigned int pAddReallocationMultiplier,
        		const unsigned int pRemoveReallocationThreshold,
        		const unsigned int pRemoveReallocationDivisor
		);
		ArrayList(const ArrayList& pOther);
		ArrayList(const IList& pOther);
		~ArrayList();
		
		ArrayList& operator=(const ArrayList& pOther);
	
		size_t getSize() const;
		int& get(const size_t pIndex) const;
		void add(const int pValue);
		int remove(const size_t pIndex);
	
	private:
		// Configuration constants
		const size_t initialCapacity;
		const unsigned int addReallocationMultiplier;
		const unsigned int removeReallocationThreshold;
		const unsigned int removeReallocationDivisor;
		
		// Mutable values
		int* values;
		size_t size;
		size_t capacity;

		// Internal methods
		int* allocateArray(
			const int* pOrigValues,
			const size_t pOrigValuesSize,
			const size_t pNewCapacity
		) const;
};

#endif