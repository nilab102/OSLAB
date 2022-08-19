#include<bits/stdc++.h>
using namespace std;
int FIFO(int pages[], int n, int capacity)
{vector<int> vec;
    queue<int> q;
    int page_faults = 0;
	for (int i=0; i<n; i++)
	{
        if (vec.size() < capacity)
		{
            vector<int>::iterator position = find(vec.begin(), vec.end(), pages[i]);
			if (position==vec.end())
			{
                vec.push_back(pages[i]);


				// increment page fault
				page_faults++;

				// Push the current page into the queue
				q.push(pages[i]);
			}
		}

		// If the set is full then need to perform FIFO
		// i.e. remove the first page of the queue from
		// set and queue both and insert the current page
		else
		{
			// Check if current page is not already
			// present in the set

            std::vector<int>::iterator position = std::find(vec.begin(), vec.end(), pages[i]);
			if (position == vec.end())
			{
				// Store the first page in the
				// queue to be used to find and
				// erase the page from the set
				int val = q.front();

				// Pop the first page from the queue
				q.pop();

				// Remove the indexes page from the set
                std::vector<int>::iterator position = std::find(vec.begin(), vec.end(), val);
                if (position != vec.end()) // == myVector.end() means the element was not found
                    vec.erase(position);
				//s.erase(val);

				// insert the current page in the set
				//s.insert(pages[i]);
                vec.push_back(pages[i]);

				// push the current page into
				// the queue
				q.push(pages[i]);

				// Increment page faults
				page_faults++;
			}
		}
	}

	return page_faults;
}

bool search(int key, vector<int>& fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

// Function to find the frame that will not be used
// recently in future after given index in pg[0..pn-1]
int predict(int pg[], vector<int>& fr, int pn, int index)
{
    // Store the index of pages which are going
    // to be used recently in future
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If a page is never referenced in future,
        // return it.
        if (j == pn)
            return i;
    }

    // If all of the frames were not in future,
    // return any of them, we return 0. Otherwise
    // we return res.
    return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{
    // Create an array for given number of
    // frames and initialize it as empty.
    vector<int> fr;

    // Traverse through page reference array
    // and check for miss and hit.
    int hit = 0;
    for (int i = 0; i < pn; i++) {

        // Page found in a frame : HIT
        if (search(pg[i], fr)) {
            hit++;
            continue;
        }

        // Page not found in a frame : MISS

        // If there is space available in frames.
        if (fr.size() < fn)
            fr.push_back(pg[i]);

            // Find the page to be replaced.
        else {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }
    }
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}
int LRU(int pages[], int n, int capacity)
{
    // To represent set of current pages. We use
    // an unordered_set so that we quickly check
    // if a page is present in set or not
   // unordered_set<int> s;
   vector<int> vec;
    // To store least recently used indexes
    // of pages.
   unordered_map<int, int> indexes;
    //vector<int >indexes;

    // Start from initial page
    int page_faults = 0;
    for (int i=0; i<n; i++)
    {
        // Check if the set can hold more pages
        if (vec.size() < capacity)
        {
            // Insert it into set if not present
            // already which represents page fault
            std::vector<int>::iterator position = std::find(vec.begin(), vec.end(), pages[i]);
            if (position == vec.end())
            {
                vec.push_back(pages[i]);

                // increment page fault
                page_faults++;
            }

            // Store the recently used index of
            // each page
            indexes[pages[i]] = i;
        }

            // If the set is full then need to perform lru
            // i.e. remove the least recently used page
            // and insert the current page
        else
        {
            // Check if current page is not already
            // present in the set
            std::vector<int>::iterator position = std::find(vec.begin(), vec.end(), pages[i]);
            if (position == vec.end())
            {
                // Find the least recently used pages
                // that is present in the set
                int lru = INT_MAX, val;
                for (auto it=vec.begin(); it!=vec.end(); it++)
                {
                    if (indexes[*it] < lru)
                    {
                        lru = indexes[*it];
                        val = *it;
                    }
                }

                std::vector<int>::iterator position = std::find(vec.begin(), vec.end(), val);
                if (position != vec.end())vec.erase(position);

                // insert the current page
                vec.push_back(pages[i]);

                // Increment page faults
                page_faults++;
            }

            // Update the current page index
            indexes[pages[i]] = i;
        }
    }

    return page_faults;
}

int main()
{
	int pages[] = {7, 0, 1, 2, 0, 3, 0, 4,
				2, 3, 0, 3, 2};
	int n = sizeof(pages)/sizeof(pages[0]);
	int capacity = 4;
	cout << FIFO(pages, n, capacity);
    optimalPage(pages, n, capacity);
    cout << LRU(pages, n, capacity);
	return 0;
}
