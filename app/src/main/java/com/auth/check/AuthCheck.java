package com.auth.check;

import android.app.Activity;
import android.content.Context;
import android.content.DialogInterface;

/**
 * Created by tone on 2020/3/27
 */
public class AuthCheck {

    static {
        System.loadLibrary("auth");
    }

    private Context context;

    public void check(Context context) {
        nativecheck(context);
        this.context=context;
    }

    public DialogInterface.OnClickListener onClickListener = new DialogInterface.OnClickListener() {
        @Override
        public void onClick(DialogInterface dialog, int which) {
            if (context instanceof Activity){
                ((Activity) context).finish();
            }
        }
    };


    public native static void nativecheck(Context context);
}
