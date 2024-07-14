module RedHttpClient.Test

import Codeware.*
import RedHttpClient.*

public class RedHttpClientTest extends ScriptableEnv {
  private let m_runner: ref<RedTest>;

  /// Lifecycle ///

  private cb func OnLoad() {
    this.m_runner = new RedTest();
    this.m_runner.Setup("RedHttpClient", [
      new HttpClientTest(),
      new AsyncHttpClientTest()
    ]);
  }

}

public static func GetRedHttpClientTest() -> ref<RedHttpClientTest> {
  return ScriptableEnv.Get(n"RedHttpClientTest") as RedHttpClientTest;
}
