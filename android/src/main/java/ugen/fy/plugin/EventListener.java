package ugen.fy.plugin;
import org.json.JSONObject;

public abstract class EventListener {
    void onEvent(String event,JSONObject json){}
    void onError(String evnet,Exception e){}
}
