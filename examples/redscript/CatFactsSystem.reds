// Copy file into r6\scripts\Awesome\
import Codeware.*
import RedData.Json.*
import RedHttpClient.*

public class CatFactDto {
  let createdAt: String;
  let updatedAt: String;
  let text: String;

  public static func FromJsonArray(json: ref<JsonArray>) -> array<ref<CatFactDto>> {
    let facts: array<ref<CatFactDto>> = [];
    let size: Uint32 = json.GetSize();
    let i: Uint32 = 0u;

    while i < size {
      let fact = FromJson(json.GetItem(i) as JsonObject, n"CatFactDto") as CatFactDto;

      ArrayPush(facts, fact);
      i += 1u;
    }
    return facts;
  }
}

public class CatFactsSystem extends ScriptableSystem {
  private let m_callbackSystem: wref<CallbackSystem>;

  /// Lifecycle ///

  private func OnAttach() {
    this.m_callbackSystem = GameInstance.GetCallbackSystem();
    this.m_callbackSystem.RegisterCallback(n"Session/Ready", this, n"OnSessionReady");
  }

  private func OnDetach() {
    this.m_callbackSystem.UnregisterCallback(n"Session/Ready", this, n"OnSessionReady");
    this.m_callbackSystem = null;
  }

  /// Game events ///

  private cb func OnSessionReady(event: ref<GameSessionEvent>) {
    let isPreGame = event.IsPreGame();

    if !isPreGame {
      return;
    }
    LogChannel(n"Info", s"== RedHttpClient - Examples ==");
    this.Example_CatFacts();
  }

  private func Shutdown() {
    LogChannel(n"Info", "");
    LogChannel(n"Info", s"== RedHttpClient - Examples ==");
  }

  /// Examples ///

  public func Example_CatFacts() {
    LogChannel(n"Info", "");
    LogChannel(n"Info", "== Cat Facts Api ==");
    let callback = HttpCallback.Create(this, n"OnCatFacts");

    AsyncHttpClient.Get(callback, "https://cat-fact.herokuapp.com/facts");
    LogChannel(n"Info", "Sending request...");
  }

  private cb func OnCatFacts(response: ref<HttpResponse>) {
    if !Equals(response.GetStatus(), HttpStatus.OK) {
      LogChannel(n"Info", s"Request failed, status code: \(response.GetStatusCode())");
      this.Shutdown();
      return;
    }
    let contentType = response.GetHeader("Content-Type");

    if !Equals(contentType, "application/json; charset=utf-8") {
      LogChannel(n"Info", s"Request failed, Json expected instead of '\(contentType)'.");
      this.Shutdown();
      return;
    }
    let json = response.GetJson();

    if !json.IsArray() {
      LogChannel(n"Info", s"Request failed, JsonArray expected instead of '\(json.GetClassName())'.");
      this.Shutdown();
      return;
    }
    let facts: array<ref<CatFactDto>> = CatFactDto.FromJsonArray(json as JsonArray);

    LogChannel(n"Info", s"\(ArraySize(facts)) cat facts:");
    for fact in facts {
      LogChannel(n"Info", s"---------------------------------------------");
      LogChannel(n"Info", s"Creation: \(fact.createdAt)");
      LogChannel(n"Info", s"Modification: \(fact.updatedAt)");
      LogChannel(n"Info", s"Fact: \(fact.text)");
    }
    this.Shutdown();
  }

}
