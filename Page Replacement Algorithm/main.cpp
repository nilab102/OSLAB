#include<bits/stdc++.h>
using namespace std;
void FIFO(int pages[], int n, int capacity)
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

				page_faults++;
				q.push(pages[i]);
			}
		}
		else
		{
            std::vector<int>::iterator position = std::find(vec.begin(), vec.end(), pages[i]);
			if (position == vec.end())
			{
				int val = q.front();


				q.pop();

                std::vector<int>::iterator position = std::find(vec.begin(), vec.end(), val);
                if (position != vec.end()) // == myVector.end() means the element was not found
                    vec.erase(position);

                vec.push_back(pages[i]);

				q.push(pages[i]);
				page_faults++;
			}
		}
	}

    cout << "No. of hits = " << n - page_faults << endl;
    cout << "No. of misses = " << page_faults << endl;
}

bool search(int key, vector<int>& fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

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

        if (j == pn)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{
    vector<int> fr;
    int hit = 0;
    for (int i = 0; i < pn; i++) {

        if (search(pg[i], fr)) {
            hit++;
            continue;
        }

        if (fr.size() < fn)
            fr.push_back(pg[i]);

        else {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }
    }
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}
void LRU(int pages[], int n, int capacity)
{

   vector<int> vec;

   unordered_map<int, int> indexes;

    int page_faults = 0;
    for (int i=0; i<n; i++)
    {

        if (vec.size() < capacity)
        {
            std::vector<int>::iterator position = std::find(vec.begin(), vec.end(), pages[i]);
            if (position == vec.end())
            {
                vec.push_back(pages[i]);

                page_faults++;
            }

            indexes[pages[i]] = i;
        }

        else
        {
            std::vector<int>::iterator position = std::find(vec.begin(), vec.end(), pages[i]);
            if (position == vec.end())
            {
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

                vec.push_back(pages[i]);
                page_faults++;
            }
            indexes[pages[i]] = i;
        }
    }

    cout << "No. of hits = " << n - page_faults << endl;
    cout << "No. of misses = " << page_faults << endl;
}

int main()
{
	int pages[] = {7, 0, 1, 2, 0, 3, 0, 4,
				2, 3, 0, 3, 2};
	int n = sizeof(pages)/sizeof(pages[0]);
	int capacity = 3;
    cout<<"FIFO Page Replacement \n";
	FIFO(pages, n, capacity);
    cout<<"\nOptimal Page Replacement \n";
    optimalPage(pages, n, capacity);
    cout<<"\nLRU Page Replacement \n";
    LRU(pages, n, capacity);
	return 0;
}
