# task-organizer
Phase 1:
*tasks are stored in vector
*new task priority is determined by linear comparisons with all existing tasks of the vector
*after each insertion the vector is being sorted
*new task will take the priority which is the middle between its two adjacent priorities. If its the first it will take the value of 256. If it's the last, it will take the value of the panultimate task increased by 256.
