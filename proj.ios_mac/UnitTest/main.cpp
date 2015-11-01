//
//  main.cpp
//  UnitTest
//
//  Created by 小七爷 on 15/11/1.
//
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"


/* We were planing to do unit test by using framework Catch.But we find it is very hard to implement
 We fix most problems that we have come across. But when we try to link with Photon, it gives mactype error
 It initially takes us about 1 week time to fix this error alst time. We don't really have time to solve it this time.
 Also none of team members know how to program in Objective-c or swift. That is why we cannnot use XTest built in Xcode.
 Instead we choose to do written unit test and add assert() into key part of our code to do unit test.
 We also do usability test， related interview and analyze report.
 
 We should evalute the risk that this could happen before we do this.
 Also we should do unit test right after when we finish one key component. This is a good reminder for us for our future work.
 */