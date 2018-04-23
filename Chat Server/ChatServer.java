//******************************************************************************
//**  File: ChatServer.java
//**  Author: Michael Ji
//******************************************************************************

import java.net.*;          // for Socket
import java.io.*;           // for IOException
import java.util.ArrayList;

public class ChatServer
{

	public static void main(String args[])
	{
		if ( args.length != 1 ) //if arg should be port number
		{
	    	System.err.println( "usage: java TcpServer port" );
	    	return;
		}
		try // make server
		{
			ServerSocket server = new ServerSocket(Integer.parseInt(args[0]));
			server.setSoTimeout(500); // change to 1ms if no work
			ArrayList<Connection> clientList = new ArrayList<Connection>();

			// infinite loop for server
			while (true)
			{
				try
				{
					// accept clients
					Socket client = server.accept();
					
					//set up streams
					InputStream in = client.getInputStream();
					DataInputStream in2 = new DataInputStream(in);
					String name = in2.readUTF();
					Connection connection = new Connection(client, name);
					clientList.add(connection);
				}
				catch (SocketTimeoutException e)
				{
					
				}

				// message reading
				// loop through everyone
					//try to Connection.in.readUTF() for message
						//if message, add name, send to all other connections except the sender
						//if bad error within connection read/write, delete the connection
				
				if (clientList.size() > 0)
				{
					// holder to delete a connection if needed
					int deleteConnection = -1;

					// loop through connections
					for (int i = 0; i < clientList.size(); i++)
					{
						if (clientList.get(i).isAvailable())
						{
							//read in message
							String messageIn = clientList.get(i).readMessage();
							//send message out to everyone until before the current client
							for (int j = 0; j < i; j++)
							{
								if (clientList.get(j).writeMessage(clientList.get(i).name + ": " + messageIn) == true)
								{
	
								}
								else // if something happens, delete
								{
									deleteConnection = j;
								}
							}
							//send message to everyone after client
							for (int j = i + 1; j < clientList.size(); j++)
							{
								if (clientList.get(j).writeMessage(clientList.get(i).name + ": " + messageIn) == true)
								{

								}
								else
								{
									deleteConnection = j;
								}
							}
						}
					}
					if (deleteConnection != -1) //deletes the connection
					{
						clientList.remove(deleteConnection);
					}
				}
			}
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}