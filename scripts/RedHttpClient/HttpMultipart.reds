public native class HttpMultipart {

  public native func AddPart(name: String, value: String) -> Void;
  public native func SetPart(name: String, value: String) -> Void;
  public native func GetPart(name: String) -> String;

}