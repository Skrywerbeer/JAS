package org.skrywerbeer;

import org.qtproject.qt.android.bindings.QtActivity;

public class MainActivity extends QtActivity {
	public MainActivity() {
		super();
		// Set them here to prevent QtActivityLoader from using a
		// different theme.
//		QT_ANDROID_DEFAULT_THEME = "ArithmeticTheme";
	}

    public void onStart() {
		super.onStart();
	}
}
