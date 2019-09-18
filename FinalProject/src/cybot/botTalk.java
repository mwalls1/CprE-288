package cybot;

import java.io.InputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.nio.charset.*;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
public class botTalk {
	Socket socket;
	public botTalk() throws UnknownHostException, IOException
	{
		socket = new Socket("192.168.1.1", 288);
	}
	public void closeCon() throws IOException
	{
		socket.close();
	}
	public void sendString(String string) {
		try {
            OutputStream outputStream = socket.getOutputStream();
            OutputStreamWriter writer = new OutputStreamWriter(outputStream, StandardCharsets.US_ASCII);
            byte[] bytes = string.getBytes(StandardCharsets.US_ASCII);
            byte[] end = new byte[1];
            end[0] = 0;
            for (int i = 0; i < bytes.length; i++) {
                outputStream.write(bytes, i, 1);
                if(i == bytes.length-1)
                {
                	outputStream.write(end, 0, 1);
                }
                outputStream.flush();
                Thread.sleep(100);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
	}
        public String readString() {
        	try {
                InputStream inputStream = socket.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream, StandardCharsets.US_ASCII));
                char[] bytes = new char[256];
                int size = reader.read(bytes);
                return new String(bytes);
            } catch (IOException e) {
                e.printStackTrace();
                return null;
            }
        }
}



