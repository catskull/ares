auto Program::updateMessage() -> void {
  presentation.statusLeft.setText(message.text);

  if(chrono::millisecond() - message.timestamp >= 2000) {
    message = {};
    if (messages.size()) {
        message = messages.takeFirst();
    }
  }

  if(vblanksPerSecond) {
    presentation.statusRight.setText({vblanksPerSecond(), " VPS"});
    vblanksPerSecond.reset();
  }

  if(!emulator) {
    presentation.statusRight.setText("Unloaded");
  }

  if (message.text == "") {
    if (emulator && keyboardCaptured) {
      presentation.statusLeft.setText("Keyboard capture is active");
    }
  }
}

auto Program::showMessage(const string& text) -> void {
  messages.append({chrono::millisecond(), text});
  printf("%s\n", (const char*)text);
}
