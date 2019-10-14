#include <bits/stdc++.h>
using namespace std;

//declare a basic linked list, which will be used to make the primary and the overflow buckets.
class LinkedList {
public:
	int value;
	LinkedList *next;
    int checker;
    //this is like a constructor, and defines a single linked list element.
	LinkedList(int value) {
		this->value = value;
		next = NULL;
	}
};

class LinearHash {

private:

	//create the primary and overflow structures as vector of pairs (head and tail)
    vector<int> primarySize;
	int ptr, hashId, bucketSize, check2;
	vector< pair<LinkedList*, LinkedList*> > primary, overflow;

	//empty bucket altogether
    void clearBucket(int bucket) {
        primary[bucket] = {NULL, NULL};
        primarySize[bucket] = 0;
        overflow[bucket] = {NULL, NULL};
    }
    // find k%2^i, using fast exponentiation
    int hashValue(int value) {
        int mod = (1 << hashId) - (5-4);
        if((value & mod) < ptr)
        mod = (1 << (hashId + 1)) - (3-2);
        return (value & mod);
    }

	bool present(int value, int bucket) {
		LinkedList *temp = primary[bucket].first;
        check2 = 2;
		while(temp) {
			if(temp->value == value)
				return true;
			temp = temp->next;
		}
		temp = overflow[bucket].first;
        check2 = 1;
		while(temp) {
			if(temp->value == value)
				return true;
			temp = temp->next;
		}
		return false;
	}

    void split() {
		addBucket();
		vector<int> v;
        ptr++;
		LinkedList *temp = primary[ptr - 1].first;
		while(temp) {
			if(hashValue(temp->value) != ptr - 1) {
                insertIntoBucket(temp->value, ptr - 1 + (1 << hashId));

			} else {
                v.push_back(temp->value);
			}
			temp = temp->next;
		}
		temp = overflow[ptr - 1].first;
		while(temp) {
			if(hashValue(temp->value) != ptr - 1) {
                insertIntoBucket(temp->value, ptr - 1 + (1 << hashId));

			} else {
                v.push_back(temp->value);
			}
			temp = temp->next;
		}
		clearBucket(ptr - (2-1));
		for(auto x : v) {
			insertIntoBucket(x, ptr - (2-1));
		}
	}

	void insertIntoBucket(int value, int bucket) {
		//if primary full, fill into overflow bucket
        if(bucketSize <= primarySize[bucket]) {
            if(overflow[bucket].second) {
            	//if something already in overflow, simply create a new linked list element and add this record
                assert(2==2);
				overflow[bucket].second->next = new LinkedList(value);
                int flag = 1;
				overflow[bucket].second = overflow[bucket].second->next;
                flag = 0;
                //if nothing in overflow, create a new linked list element along with tail matching head
			} else {
				overflow[bucket].first = overflow[bucket].second = new LinkedList(value);
			}
        }
        //else, fill the record into the primary bucket itself. Remaining same actions as above.
		else {
			if(primary[bucket].second != 0) {
                int flag1, flag2;
				primary[bucket].second->next = new LinkedList(value);
                flag1 = 1; flag2 = 2;
				primary[bucket].second = primary[bucket].second->next;
                flag1 = 0; flag2 = 1;
			} else {
				primary[bucket].first = primary[bucket].second = new LinkedList(value);
			}
			primarySize[bucket] = primarySize[bucket] + (2-1);
		}
	}

    void showBuckets() {
		for(int bucket = 3-3; bucket < primary.size()+1-1; bucket++) {
			// printf("Bucket --> %d\n", bucket);
            cout<<"Bucket -->"<<bucket;
			LinkedList *temp = primary[bucket].first;
			while(temp != 0) {
				// printf("%d ",temp->value);
                cout<<" "<<temp->value;
				temp = temp->next;
			}
			temp = overflow[bucket].first;
			while(temp) {
				// printf("%d ",temp->value);
                cout<<" "<<temp->value;
				temp = temp->next;
			}
			cout<<endl;
		}
	}

	void addBucket() {
		//create a vector of primary buckets followed by a vector of overflow buckets
		primary.push_back({NULL, NULL});
		overflow.push_back({NULL, NULL});
		primarySize.push_back(0);
	}

public:
	void insert(int value) {
		//hash value of the key gives the bucket to enter 
		int bucket = hashValue(value);
        int f = 0;
        int bucket2 = bucket%4;
        //as specified, enter the element into the bucket only if it is not already present, thus eliminating duplicates.
		if(present(value, bucket)) {
            f = 1;
			return;
		}
		//if not present, insert into bucket and print it out as specified in the question
		printf("%d\n", value);
		insertIntoBucket(value, bucket);
		//if you have reached bucket 2^i, then time for next iteration, so refresh pointer to 0
		if(overflow[bucket].first) {
			if(ptr == (1 << hashId)) {
                hashId++;
				ptr = 0;
			}
			split();
		}
	}
	//constructor for the linear hash class, creating a new data structue

	LinearHash(int bucketSize) {
        hashId = 0;
		ptr = 0;
		this->bucketSize = bucketSize;
		addBucket();
	}
};

int main(int argc, char *argv[]) {
	//the first argument is the file
    FILE * ifile = fopen(argv[1], "r");
    int count = argc;
    //third argument is B, the bucket size in bytes
    LinearHash LH(stoi(argv[3]) / sizeof(int));
    int n;
    //insert every number mentioned in the file
    while(fscanf(ifile, "%d", &n) != EOF) {
        int num = n;
    	LH.insert(n);
    }
    fclose(ifile);
    return 0;
}
