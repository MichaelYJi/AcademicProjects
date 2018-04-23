//******************************************************************************
//**  File: Connection.java
//**  Author: Michael Ji
//******************************************************************************
import java.net.*;          // for Socket
import java.io.*;           // for IOException

// Encapsulates client socket, name, and message data.
public class Connection
{
	public String name;
	private DataInputStream in;
	private DataOutputStream out;
	private InputStream inStream;
	private OutputStream outStream;
	private Socket client;

	// constructor to encapsulate client socket, name, in/out streams
	public Connection(Socket clientSocket, String clientName) throws IOException
	{
		client = clientSocket;
		name = clientName;
		inStream = client.getInputStream();
		outStream = client.getOutputStream();
		in = new DataInputStream(inStream);
		out = new DataOutputStream(outStream);
	}
	
	// reads message from client
	public String readMessage() throws IOException //from client
	{
		return in.readUTF();
	}

	// writes a message to client
	public boolean writeMessage(String fromClient) throws IOException //to client
	{
		try 
		{
			out.writeUTF(fromClient);
		}
		catch(Exception e)
		{
			return false;
		}
		return true;
	}

	// checks if client has message available
	public boolean isAvailable() throws IOException
	{
		return inStream.available() > 0;
	}

	public void close() throws IOException
	{
		client.close();
	}
}