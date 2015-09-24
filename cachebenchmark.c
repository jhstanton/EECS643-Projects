#include<stdio.h>
#include<time.h>
#include<strings.h>
#include<stdlib.h>
#include<unistd.h>


#define NbrPlanes 64
#define NbrRows 1024
#define NbrCols 1024
#define NbrIterations 100

int32_t Data[NbrPlanes][NbrRows][NbrCols];

int main(int argc, const char * argv[]) {
  
  int32_t I, J, K = 0;
  int32_t L = NbrIterations;
  int32_t X = 0;
  long inner_time_sum = 0;

  time_t StartTime, EndTime, InnerStartTime, InnerEndTime;

  printf(">>CacheBenchmark: Starting \n");
  
  time(&StartTime);
  printf(">>CacheBenchmark: Start: Time = %12ld    %s\n", StartTime, ctime(&StartTime));
  
  printf(">>Size of int: %ld; Size of long int: %ld; Size of time_t: %ld\n", sizeof( int ), sizeof( long int), sizeof( time_t));

  for(I = 0; I < NbrPlanes; I++){
    for(J = 0; J < NbrRows; J++){
      for(K = 0; K < NbrCols; K++) {
	//X = Data[I][J][K];		
	Data[I][J][K] = 0;
      }
    }
  }

  sleep( 1 );
  time (&StartTime);
  for( L=0; L < NbrIterations; L++){
    time( &InnerStartTime);
    for( I = 0; I < NbrPlanes; I++){
      for( J = 0; J < NbrRows; J++){
	for( K = 0; K < NbrCols; K++){
	  X = Data[I][J][K];
	}
      }
    }
    time( &InnerEndTime );
    inner_time_sum += InnerEndTime - InnerStartTime;
  }

  time( &EndTime );
  
  printf( ">>>>X: %d\n", X);
  printf(">>CacheBenchmark: Start %12ld; End: %12ld; Delta: %12ld; InnerLoopAvg: %12ld\n", 
	 StartTime, EndTime, (EndTime - StartTime), inner_time_sum / NbrIterations);

  inner_time_sum = 0;

  sleep( 1 );

  time( &StartTime );
  for(L = 0; L < NbrIterations; L++){
    time( &InnerStartTime);
    for( K = 0; K < NbrCols; K++){
      for( J = 0; J < NbrRows; J++) {
	for ( I = 0;  I < NbrPlanes; I++) {
	  X = Data[I][J][K];
	}
      }
    }
    time( &InnerEndTime );
    inner_time_sum += InnerEndTime - InnerStartTime;
  }

  time ( &EndTime);

  printf(">>>>X: %d\n", X);
  printf(">>CacheBenchmark: Start: %12ld; End: %12ld; Delta: %12ld; InnerLoopAvg: %12ld\n", 
	 StartTime, EndTime, (EndTime - StartTime), inner_time_sum / NbrIterations);
  return 1;
}