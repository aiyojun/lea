export interface Handle<T> {
    match(): boolean;
    apply(): T;
}

export function handle<T>(options: Handle<T>[]): T {
    for (let i = 0; i < options.length; i++) {
        const option = options[i]
        if (option.match())
            return option.apply()
    }
    return null
}