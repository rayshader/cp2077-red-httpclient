import Codeware.*

public class MainTest extends ScriptableEnv {
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

public static func GetMainTest() -> ref<MainTest> {
  return ScriptableEnv.Get(n"MainTest") as MainTest;
}
