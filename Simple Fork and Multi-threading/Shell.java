//******************************************************************************
//**  File: Shell.java
//**  Author: Michael Ji
//******************************************************************************
import java.util.*;
public class Shell extends Thread
{
	StringBuffer inputBuf;
	static int number;
	public Shell()
	{
		inputBuf = new StringBuffer();
		number = 0;	//track Shell[number];
	}

	public void run()
	{
		while (true) 
		{
			inputBuf = new StringBuffer();	//input buffer
			SysLib.cerr("Shell[" + number + "]% ");
			number++;

			SysLib.cin(inputBuf);	//read in
			String inputString = inputBuf.toString();	//converts to string
			if (inputString.equals("exit"))	//exit command
			{
				break;
			}
			String[] args = SysLib.stringToArgs(inputString);	//convert array
			//get length
			int argsLength = args.length;	//total args
			int c = 0;
			int counter = 0;
			//make arraylist
			List<String> list = new ArrayList<String>();
			while (c < argsLength)
			{
			//add to arrlist
				list.add(args[c]);
				c++;
				if (c == argsLength) //if reaches end of args
				{
					String[] commandIn = list.toArray(new String[list.size()]);	//arraylist to array
					SysLib.exec(commandIn);
					SysLib.join();	//wait since ;
					for (int i = 0; i < counter; i++)	//buffer at end for & before break
					{
						SysLib.join();
					}
					break;
				}
				if (args[c].equals("&")) //concurrent
				{
					String[] commandIn = list.toArray(new String[list.size()]); //arraylist to array
					SysLib.exec(commandIn);
					list.clear();
					c++;
					counter++;
				}
				if (args[c].equals(";")) //wait
				{
					String[] commandIn = list.toArray(new String[list.size()]); //arraylist to array
					SysLib.exec(commandIn);
					SysLib.join();
					list.clear();
					c++;
				}
			}
		}
		SysLib.exit();
	}
}