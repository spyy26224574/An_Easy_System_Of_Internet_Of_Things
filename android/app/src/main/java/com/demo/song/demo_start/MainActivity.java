package com.demo.song.demo_start;

import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;


public class MainActivity extends AppCompatActivity {
    Button conbtn;
    Button sendbtn;
    EditText ipedt;
    EditText portedt;
    EditText sendedt;
    TextView recedt;

    String ip;
    String port;

    Socket socket = null;
    BufferedWriter writer = null;
    BufferedReader reader = null;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findView();
        conbtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                connect();
            }
        });
        sendbtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                send();
            }
        });
    }



    private void connect() {
        ip = ipedt.getText().toString();
        port = portedt.getText().toString();

        AsyncTask<Void,String,Void> read = new AsyncTask<Void, String, Void>() {
            @Override
            protected Void doInBackground(Void... params) {
                try {
                    socket = new Socket(ip,Integer.parseInt(port));
                    writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
                    reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    publishProgress("@success");
                } catch (IOException e) {
                    e.printStackTrace();
                }
                String line;
                try {
                    while ((line = reader.readLine())!= null) {
                        publishProgress(line);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }

                return null;
            }

            @Override
            protected void onProgressUpdate(String... values) {

                if (values[0].equals("@success")) {
                    Toast.makeText(MainActivity.this, "链接成功！", Toast.LENGTH_SHORT).show();
                }
                recedt.append("receive："+values[0]+"\n");
                super.onProgressUpdate(values);
            }
        };
        read.execute();
    }

    private void send() {
        recedt.append("send："+sendedt.getText().toString()+"\n");
        try {
            writer.write(sendedt.getText().toString()+"\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
        sendedt.setText("");
    }




    private void findView() {
        conbtn  = (Button)findViewById(R.id.btn);
        sendbtn = (Button)findViewById(R.id.send_btn);
        ipedt = (EditText)findViewById(R.id.ip);
        portedt = (EditText)findViewById(R.id.port);
        sendedt = (EditText)findViewById(R.id.send_edt);
        recedt = (TextView)findViewById(R.id.receive);

    }
}
