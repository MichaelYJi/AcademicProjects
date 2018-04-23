//******************************************************************************
//**  File: Scheduler.java
//**  Author: Michael Ji
//**  Edits from line 64
//******************************************************************************

import java.util.*;

public class Scheduler extends Thread
{
    private Vector queue0;
    private Vector queue1;
    private Vector queue2;
    private int timeSlice;
    private static final int DEFAULT_TIME_SLICE = 500;

    // New data added to p161 
    private boolean[] tids; // Indicate which ids have been used
    private static final int DEFAULT_MAX_THREADS = 10000;

    // A new feature added to p161 
    // Allocate an ID array, each element indicating if that id has been used
    private int nextId = 0;

    private void initTid( int maxThreads )
    {
		tids = new boolean[maxThreads];
		for ( int i = 0; i < maxThreads; i++ )
	    	tids[i] = false;
    }

    // A new feature added to p161 
    // Search an available thread ID and provide a new thread with this ID
    private int getNewTid( )
    {
		for ( int i = 0; i < tids.length; i++ ) 
		{
	    	int tentative = ( nextId + i ) % tids.length;
	    	if ( tids[tentative] == false )
	    	{
			tids[tentative] = true;
			nextId = ( tentative + 1 ) % tids.length;
			return tentative;
	    	}
		}
		return -1;
    }

    // A new feature added to p161 
    // Return the thread ID and set the corresponding tids element to be unused
    private boolean returnTid( int tid )
    {
		if ( tid >= 0 && tid < tids.length && tids[tid] == true )
		{
		    tids[tid] = false;
		    return true;
		}
		return false;
    }

    // A new feature added to p161 
    // Retrieve the current thread's TCB from the queue
    public TCB getMyTcb( ) // changed this cause you need to find the tcb
    {
		Thread myThread = Thread.currentThread( ); // Get my thread object
		synchronized( queue0 ) 
		{
	   		for ( int i = 0; i < queue0.size( ); i++ ) 
	   		{
				TCB tcb = ( TCB )queue0.elementAt( i );
				Thread thread = tcb.getThread( );
				if ( thread == myThread ) // if this is my TCB, return it
				return tcb;
	   		}
		}
		synchronized( queue1 ) 
		{
	   		for ( int i = 0; i < queue1.size( ); i++ ) 
	   		{
				TCB tcb = ( TCB )queue1.elementAt( i );
				Thread thread = tcb.getThread( );
				if ( thread == myThread ) // if this is my TCB, return it
				return tcb;
	   		}
		}
		synchronized( queue2 ) 
		{
	   		for ( int i = 0; i < queue2.size( ); i++ ) 
	   		{
				TCB tcb = ( TCB )queue2.elementAt( i );
				Thread thread = tcb.getThread( );
				if ( thread == myThread ) // if this is my TCB, return it
				return tcb;
	   		}
		}
		return null;
    }

    // A new feature added to p161 
    // Return the maximal number of threads to be spawned in the system
    public int getMaxThreads( )
    {
		return tids.length;
    }

    public Scheduler( )
    {
		timeSlice = DEFAULT_TIME_SLICE;
		queue0 = new Vector( );
		queue1 = new Vector( );
		queue2 = new Vector( );
		initTid( DEFAULT_MAX_THREADS );
    }

    public Scheduler( int quantum )
    {
		timeSlice = quantum;
		queue0 = new Vector( );
		queue1 = new Vector( );
		queue2 = new Vector( );
		initTid( DEFAULT_MAX_THREADS );
    }

    // A new feature added to p161 
    // A constructor to receive the max number of threads to be spawned
    public Scheduler( int quantum, int maxThreads )
    {
		timeSlice = quantum;
		queue0 = new Vector( );
		queue1 = new Vector( );
		queue2 = new Vector( );
		initTid( maxThreads );
    }

    private void schedulerSleep( )
    {
		try
		{
		    Thread.sleep( timeSlice );
		} 
		catch ( InterruptedException e ) { }
    }

    // A modified addThread of p161 example
    public TCB addThread( Thread t )	// all new added to queue0
    {
		TCB parentTcb = getMyTcb( ); // get my TCB and find my TID
		int pid = ( parentTcb != null ) ? parentTcb.getTid( ) : -1;
		int tid = getNewTid( ); // get a new TID
		if ( tid == -1)
	    	return null;
		TCB tcb = new TCB( t, tid, pid ); // create a new TCB
		queue0.add( tcb );
		return tcb;
    }

    // A new feature added to p161
    // Removing the TCB of a terminating thread
    public boolean deleteThread( )
    {
		TCB tcb = getMyTcb( ); 
		if ( tcb!= null )
	    	return tcb.setTerminated( );
		else
	    	return false;
    }

    public void sleepThread( int milliseconds )
    {
		try 
		{
	    	sleep( milliseconds );
		} 
		catch ( InterruptedException e ) { }
    }
    
    // A modified run of p161
    public void run( )
    {
		Thread current = null;
		while ( true )
		{
	    	try 
	    	{
	    		runQ0();
	    		runQ1();
	    		runQ2();
	    	} 
	    	catch ( NullPointerException e3 ) { };
		}
    }

    // attempts to finish processes in queue0 in 1 time slice of 500ms
    // moves unfinished processes into queue1
    public void runQ0()
    {
    	while (queue0.size() > 0)
    	{
    		TCB currentTCB = (TCB)queue0.firstElement( );
    		if ( currentTCB.getTerminated( ) == true )
				{
				    queue0.remove( currentTCB );
				    returnTid( currentTCB.getTid( ) );
				    continue;
				}
			Thread current = currentTCB.getThread( ); //added Thread
			if ( current != null ) 
			{
				if ( current.isAlive( ) )
					current.resume();
		 		else 
		 		{ // Spawn must be controlled by Scheduler
				current.start( ); // Scheduler must start a new thread
				}
			}
			schedulerSleep( ); // 500 ms
			synchronized ( queue0 ) 
			{
			    if ( current != null && current.isAlive( ) )
					current.suspend();
			}
			if ( currentTCB.getTerminated( ) == true )
			{
				queue0.remove( currentTCB );
				returnTid( currentTCB.getTid( ) );
				continue;
			}
		    queue0.remove( currentTCB ); // rotate this TCB to queue1
		    queue1.add( currentTCB );
    	}
    }

    // attempts to finish processes in queue1 in 1000ms divided into 2 time slices
    // checks queue0 in between time slices and attempts to complete any processes in that queue
    // moves unfinished processes from queue1 to queue2
    public void runQ1()
    {
    	while (queue1.size() > 0)
    	{
    		TCB currentTCB = (TCB)queue1.firstElement( );
    		for (int i = 0; i < 2; i++) // does 500ms sleep x2 if needed for 1000ms quantom
    		{
				Thread current = currentTCB.getThread( ); //starts, added thread
				if ( current != null ) 
				{
					if ( current.isAlive( ) )
						current.resume();
		 			else 
		 			{ // Spawn must be controlled by Scheduler
						current.start( ); // Scheduler must start a new thread
					}
				}
				schedulerSleep( );
				synchronized (queue1) // if not finished, suspend
				{
					if ( current != null && current.isAlive( ) )
						current.suspend(); 
				}
    			
    			if ( currentTCB.getTerminated( ) == true ) // if finished, remove
				{
					queue1.remove( currentTCB );
					returnTid( currentTCB.getTid( ) );
					if (queue0.size() > 0)
					{
						runQ0();
					}
					break;
				}

				if (i == 1) // at end of loop and not finished, move to queue2
				{
					queue1.remove( currentTCB );
					queue2.add( currentTCB );
				}

				if (queue0.size() > 0) // catches if anything is added to queue0
				{
					runQ0();
				}
			}
    	}
    }

    // attempts to finish processes in 2000ms in 4 time slices
    // checks queue1 in between time slices and attempts to complete any processes in that queue
    // moves unfinished processes to the back of queue2
    public void runQ2()
    {
    	while (queue2.size() > 0)
    	{
    		TCB currentTCB = (TCB)queue2.firstElement( );
    		for (int i = 0; i < 4; i++) // does 500ms sleep 4x for 2000ms quantum
    		{
				Thread current = currentTCB.getThread( ); // starts, added thread
				if ( current != null ) 
				{
					if ( current.isAlive( ) )
						current.resume();
		 			else 
		 			{ // Spawn must be controlled by Scheduler
						current.start( ); // Scheduler must start a new thread
					}
				}
				schedulerSleep( );
				synchronized (queue1) // if not finished, suspend
				{
					if ( current != null && current.isAlive( ) )
						current.suspend(); 
				}
    			
    			if ( currentTCB.getTerminated( ) == true ) // if finished, remove
				{
					queue2.remove( currentTCB );
					returnTid( currentTCB.getTid( ) );
					if (queue0.size() > 0) // check if anything is in queue0
					{
						runQ0();
					}
					if (queue1.size() > 0) // check if anything is in queue1
					{
						runQ1();
					}
					break; //ends loop
				}

				if (i == 3) // at end of loop didnt finish, rotate to end
				{
					queue2.remove( currentTCB );
					queue2.add( currentTCB );
				}

				if (queue0.size() > 0) // checks if anything is added to queue0
				{
					runQ0();
				}
				if (queue1.size() > 0) // checks if anything is added to queue1
				{
					runQ1();
				}
			}
    	}
    }

}
