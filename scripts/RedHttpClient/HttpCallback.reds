public native struct HttpCallback {

  public static func Create(target: wref<IScriptable>, function: CName, opt data: array<Variant>) -> HttpCallback {
    let self: HttpCallback;

    self.target = target;
    self.function = function;
    self.data = data;
    return self;
  }

  public native let target: wref<IScriptable>;
  public native let function: CName;
  public native let data: array<Variant>;

}