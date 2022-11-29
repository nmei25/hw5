

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
//backtracking search function to schedule the nurses
bool helpNurse(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<unsigned int> track);

// Add your implementation of schedule() and other helper functions here
bool helpNurse(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<unsigned int> track)
{
	//sched.size()-1 = day
	//base case
	//if you reach end without backtracking, then schedule is good
	//avail.size = orkers' availability over an n-day period
	if ((sched.size()-1) >= avail.size())
	{
		//if there is extra day, then get rid of extra day
		if (sched[sched.size()-1].size() == 0) {
				sched.pop_back();
		}
		return true;
	}
	//days start with 0
	//checking if dailyneed of nurses has been met
	if (sched[sched.size()-1].size() == dailyNeed)
	{
		//move onto the next day
		std::vector<Worker_T> empty;
		//oushback = adding another day to schedule
		sched.push_back(empty);
		return helpNurse(avail,dailyNeed,maxShifts,sched,track);
	}
	//count nurser's available on that day
	for(unsigned int i = 0; i < avail[0].size(); i++)
	{
		//checking if nurse [i] is available and they work less than max # of shifts
		if (avail[sched.size()-1][i] == true && track[i] < maxShifts)
		{
			std::vector<unsigned int> copyTrack(track);
			copyTrack[i]++;
			//scheduling nurse temporarily
			sched[sched.size()-1].push_back(i);
			AvailabilityMatrix copyAvail = avail;
			//can't be schedule for same day again
			copyAvail[sched.size()-1][i] = false;
			//run through each day
			if(helpNurse(copyAvail,dailyNeed,maxShifts,sched,copyTrack))
			{
					return true;
			}
			//reverse what we did to try a different nurse
			sched[sched.size()-1].pop_back();
		}
	}
	//dailyneed = how many nurses are needed
	//if there are less nurses avaiable than daily need, return false
	if (sched[sched.size()-1].size() == 0) {
		sched.pop_back();
	}
	return false; 
}
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
	if(avail.size() == 0U){
			return false;
	}
	sched.clear();
	// Add your code below
	//push empty vector
	//schedule now has at least one day
	std::vector<Worker_T> empty;
	sched.push_back(empty);
	std::vector<unsigned int> track; 
	for (unsigned int i =0; i < avail[0].size();i++)
	{
		//that each nurse has been scheduled for 0 days, beginning
		track.push_back(0);
	}
	return helpNurse(avail, dailyNeed, maxShifts, sched, track);
}

