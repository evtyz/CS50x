package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;

public class PokemonActivity extends AppCompatActivity {
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private TextView descTextView;
    private Button catchView;
    private ImageView spriteView;

    private String url;
    private RequestQueue requestQueue;
    private boolean caught;

    private SharedPreferences sharedPref;

    private String name;
    private int id;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);

        requestQueue = Volley.newRequestQueue(getApplicationContext());
        url = getIntent().getStringExtra("url");

        sharedPref = this.getPreferences(Context.MODE_PRIVATE);
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        descTextView = findViewById(R.id.pokemon_desc);
        catchView = findViewById(R.id.catch_button);
        spriteView = findViewById(R.id.pokemon_image);

        load();
    }



    public void load() {
        type1TextView.setText("");
        type2TextView.setText("");
        descTextView.setText("");

        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    name = response.getString("name");
                    String displayName = name.substring(0, 1).toUpperCase() + name.substring(1);
                    nameTextView.setText(displayName);
                    caught = sharedPref.getBoolean(name, false);
                    if (caught) {
                        catchView.setText("Release");
                    }
                    else
                    {
                        catchView.setText("Catch");
                    }
                    id = response.getInt("id");

                    numberTextView.setText(String.format("#%03d", id));

                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");
                        type = type.substring(0, 1).toUpperCase() + type.substring(1);
                        if (slot == 1) {
                            type1TextView.setText(type);
                        }
                        else if (slot == 2) {
                            type2TextView.setText(type);
                        }
                    }

                    String descURL = String.format("https://pokeapi.co/api/v2/pokemon-species/%d/", id);
                    JsonObjectRequest request2 = new JsonObjectRequest(Request.Method.GET, descURL, null, new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try {
                                Log.d("check", "1");
                                JSONArray descEntries = response.getJSONArray("flavor_text_entries");
                                for (int i = 0; i < descEntries.length(); i++) {

                                    JSONObject entry = descEntries.getJSONObject(i);
                                    String lang = entry.getJSONObject("language").getString("name");

                                    if (lang.equals("en")) {
                                        String text = entry.getString("flavor_text");

                                        descTextView.setText(text);
                                        break;
                                    }
                                }
                            } catch (JSONException e) {
                                Log.e("jsoncheck", "Pokemon desc json error", e);
                            }
                        }
                    }, new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("jsoncheck", "Pokemon desc details error", error);
                        }
                    });
                    requestQueue.add(request2);

                    String imageURL = response.getJSONObject("sprites").getString("front_default");
                    new DownloadSpriteTask().execute(imageURL);
                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });
        requestQueue.add(request);


    }


    public void toggleCatch(View view) {
        caught = !caught;
        if (caught) {
            catchView.setText("Release");
        }
        else {
            catchView.setText("Catch");
        }
        sharedPref.edit().putBoolean(name, caught).commit();
    }

    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                return BitmapFactory.decodeStream(url.openStream());
            }
            catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            spriteView.setImageBitmap(bitmap);
        }
    }

}
